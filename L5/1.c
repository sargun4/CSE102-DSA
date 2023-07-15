// // #include <stdio.h>
// // #include <stdlib.h>

// // #define MAX_CITIES 100001

// // typedef struct {
// //     int soldiers;
// //     int visited;
// // } City;

// // City cities[MAX_CITIES];

// // int conquerableKingdoms(int city, int K) {
// //     int count = 0;
// //     cities[city].visited = 1;
// //     // Check if the current city has a kingdom
// //     if (cities[city].soldiers == 0) {
// //         int i = 1;
// //         while (i <= K && city + i < MAX_CITIES && cities[city + i].soldiers == 0) {
// //             // Mark consecutive cities as visited
// //             cities[city + i].visited = 1;
// //             i++;
// //         }
// //         count++;
// //     }
// //     // Recursively conquer kingdoms in connected cities
// //     for (int i = city + 1; i < MAX_CITIES && cities[i].visited == 0; i++) {
// //         if (cities[i].soldiers == 0) {
// //             int j = 1;
// //             while (j <= K && i + j < MAX_CITIES && cities[i + j].soldiers == 0) {
// //                 cities[i + j].visited = 1;
// //                 j++;
// //             }
// //             count++;
// //         }
// //     }   
// //     return count;
// // }
// // int main() {
// //     int N, K;
// //     scanf("%d %d", &N, &K);
// //     // Read the presence of soldiers in each city
// //     for (int i = 1; i <= N; i++) {
// //         scanf("%d", &cities[i].soldiers);
// //         cities[i].visited = 0;
// //     }
// //     // Read the connections between cities
// //     for (int i = 1; i < N; i++) {
// //         int u, v;
// //         scanf("%d %d", &u, &v);    }
// //     int conquered = conquerableKingdoms(1, K);
// //     printf("%d\n", conquered);    
// //     return 0;
// // }
// #include <stdio.h>
// #include <stdlib.h>

// typedef struct Node {
//     int city;
//     struct Node* next;
// } Node;

// Node* graph[100001];  // Assuming the maximum number of cities is 100000

// void addEdge(int u, int v) {
//     Node* newNode = (Node*)malloc(sizeof(Node));
//     newNode->city = v;
//     newNode->next = graph[u];
//     graph[u] = newNode;
// }

// int dfs(int current, int k) {
//     int conquered = 0;
//     int consecutive = 0;

//     Node* adjacent = graph[current];
//     while (adjacent != NULL) {
//         int nextCity = adjacent->city;

//         if (consecutive + 1 <= k)
//             consecutive++;
//         else
//             consecutive = 1;

//         if (consecutive == 1)
//             conquered++;

//         conquered += dfs(nextCity, k);

//         adjacent = adjacent->next;
//     }

//     return conquered;
// }

// int main() {
//     int N, K;
//     scanf("%d %d", &N, &K);

//     int* soldiers = (int*)malloc((N + 1) * sizeof(int));  // +1 for 1-based indexing
//     for (int i = 1; i <= N; i++) {
//         scanf("%d", &soldiers[i]);
//     }

//     for (int i = 1; i <= N - 1; i++) {
//         int u, v;
//         scanf("%d %d", &u, &v);
//         addEdge(u, v);
//     }

//     int conquered = dfs(1, K);

//     printf("%d\n", conquered);
//     free(soldiers);
//     return 0;
// }
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int city;
    struct Node* next;
} Node;

Node* graph[100001];  // Assuming the maximum number of cities is 100000

void addEdge(int u, int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->city = v;
    newNode->next = graph[u];
    graph[u] = newNode;
}

int dfs(int current, int k, int prevSoldiers) {
    int conquered = 0;
    Node* adjacent = graph[current];

    while (adjacent != NULL) {
        int nextCity = adjacent->city;

        if (prevSoldiers == 0 && graph[nextCity] != NULL && graph[nextCity]->next == NULL) {
            if (k > 0) {
                conquered++;
                k--;
            }
        } else {
            conquered += dfs(nextCity, k, graph[nextCity] == NULL || graph[nextCity]->next == NULL);
        }

        adjacent = adjacent->next;
    }

    return conquered;
}

int main() {
    int N, K;
    scanf("%d %d", &N, &K);

    int* soldiers = (int*)malloc((N + 1) * sizeof(int));  // +1 for 1-based indexing
    for (int i = 1; i <= N; i++) {
        scanf("%d", &soldiers[i]);
    }

    for (int i = 1; i <= N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }

    int conquered = dfs(1, K, soldiers[1]);

    printf("%d\n", conquered+1);
    free(soldiers);
    return 0;
}
