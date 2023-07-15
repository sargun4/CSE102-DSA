// #include <stdio.h>
// #include <stdlib.h>

// struct Node {
//     int house;
//     struct Node* next;
// };

// struct Graph {
//     int numHouses;
//     struct Node** adjList;
// };

// struct Node* createNode(int house) {
//     struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
//     newNode->house = house;
//     newNode->next = NULL;
//     return newNode;
// }

// struct Graph* createGraph(int numHouses) {
//     struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
//     graph->numHouses = numHouses;
//     graph->adjList = (struct Node**)malloc((numHouses + 1) * sizeof(struct Node*));

//     for (int i = 1; i <= numHouses; i++) {
//         graph->adjList[i] = NULL;
//     }

//     return graph;
// }

// void addEdge(struct Graph* graph, int house1, int house2) {
//     // Add edge from house1 to house2
//     struct Node* newNode = createNode(house2);
//     newNode->next = graph->adjList[house1];
//     graph->adjList[house1] = newNode;

//     // Add edge from house2 to house1
//     newNode = createNode(house1);
//     newNode->next = graph->adjList[house2];
//     graph->adjList[house2] = newNode;
// }
// int dfs(struct Graph* graph, int currentHouse, int targetHouse, int towardsMansion, int* visited) {
//     visited[currentHouse] = 1;

//     if (currentHouse == targetHouse) {
//         return 1;  // Found Ishu's house
//     }

//     struct Node* temp = graph->adjList[currentHouse];
//     while (temp != NULL) {
//         int neighborHouse = temp->house;

//         if (visited[neighborHouse] == 0 && (neighborHouse != 1 || !towardsMansion)) {
//             if (dfs(graph, neighborHouse, targetHouse, towardsMansion, visited)) {
//                 return 1;  // Found Ishu's house through this path
//             }
//         }

//         temp = temp->next;
//     }

//     return 0;  // Ishu's house not found through any path
// }

// int main() {
//     int numHouses;
//     scanf("%d", &numHouses);

//     struct Graph* graph = createGraph(numHouses);

//     for (int i = 1; i < numHouses; i++) {
//         int house1, house2;
//         scanf("%d %d", &house1, &house2);
//         addEdge(graph, house1, house2);
//     }

//     int numQueries;
//     scanf("%d", &numQueries);

//     for (int i = 0; i < numQueries; i++) {
//         char queryType[10];
//         int targetHouse, startHouse;

//         scanf("%s %d %d", queryType, &targetHouse, &startHouse);

//         int towardsMansion = (queryType[0] == 't');
//         int* visited = (int*)calloc(numHouses + 1, sizeof(int));
//         int result = dfs(graph, startHouse, targetHouse, towardsMansion,visited);

//         if (result) {
//             printf("YES\n");
//         } else {
//             printf("NO\n");
//         }
//     }

//     return 0;
// }
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int house;
    struct Node* next;
} Node;

typedef struct Graph {
    int numHouses;
    Node** adjList;
} Graph;

Graph* createGraph(int numHouses) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numHouses = numHouses;
    graph->adjList = (Node**)malloc((numHouses + 1) * sizeof(Node*));

    for (int i = 1; i <= numHouses; i++) {
        graph->adjList[i] = NULL;
    }

    return graph;
}

void addEdge(Graph* graph, int u, int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->house = v;
    newNode->next = graph->adjList[u];
    graph->adjList[u] = newNode;

    newNode = (Node*)malloc(sizeof(Node));
    newNode->house = u;
    newNode->next = graph->adjList[v];
    graph->adjList[v] = newNode;
}

void freeGraph(Graph* graph) {
    for (int i = 1; i <= graph->numHouses; i++) {
        Node* temp = graph->adjList[i];
        while (temp != NULL) {
            Node* prev = temp;
            temp = temp->next;
            free(prev);
        }
    }

    free(graph->adjList);
    free(graph);
}

int* createVisitedArray(int numHouses) {
    int* visited = (int*)malloc((numHouses + 1) * sizeof(int));

    for (int i = 1; i <= numHouses; i++) {
        visited[i] = 0;
    }

    return visited;
}

void freeVisitedArray(int* visited) {
    free(visited);
}

int dfs(Graph* graph, int* visited, int currentHouse, int targetHouse, int towardsMansion) {
    visited[currentHouse] = 1;

    if (currentHouse == targetHouse) {
        return 1;
    }

    Node* temp = graph->adjList[currentHouse];
    while (temp != NULL) {
        int neighborHouse = temp->house;
        if (visited[neighborHouse] == 0 && (neighborHouse != 1 || towardsMansion == 0)) {
            if (dfs(graph, visited, neighborHouse, targetHouse, towardsMansion)) {
                return 1;
            }
        }
        temp = temp->next;
    }

    return 0;
}
int main() {
    int numHouses;
    scanf("%d", &numHouses);

    Graph* graph = createGraph(numHouses);

    for (int i = 1; i < numHouses; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(graph, u, v);
    }

    int numQueries;
    scanf("%d", &numQueries);

    while (numQueries--) {
        char query[10];
        int x, y;
        scanf("%s %d %d", query, &x, &y);

        int* visited = createVisitedArray(numHouses);

        int towardsMansion = (query[0] == 't') ? 1 : 0;

        if (dfs(graph, visited, x, y, towardsMansion)) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }

        freeVisitedArray(visited);
    }

    freeGraph(graph);

    return 0;
}
