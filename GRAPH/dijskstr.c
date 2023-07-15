#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_VERTICES 1000
#define INF INT_MAX

int graph[MAX_VERTICES][MAX_VERTICES];
int dist[MAX_VERTICES];
bool visited[MAX_VERTICES];
int numVertices;

void initializeGraph() {
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            graph[i][j] = INF;
        }
    }
}

void addEdge(int u, int v, int weight) {
    graph[u][v] = weight;
    graph[v][u] = weight;
}

int findMinDistance() {
    int minDist = INF;
    int minIndex = -1;

    for (int i = 0; i < numVertices; i++) {
        if (!visited[i] && dist[i] < minDist) {
            minDist = dist[i];
            minIndex = i;
        }
    }

    return minIndex;
}

void dijkstra(int startVertex) {
    for (int i = 0; i < numVertices; i++) {
        dist[i] = INF;
        visited[i] = false;
    }

    dist[startVertex] = 0;

    for (int count = 0; count < numVertices - 1; count++) {
        int u = findMinDistance();
        visited[u] = true;

        for (int v = 0; v < numVertices; v++) {
            if (!visited[v] && graph[u][v] != INF && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
}

int main() {
    int numEdges, startVertex;
    scanf("%d %d %d", &numVertices, &numEdges, &startVertex);

    initializeGraph();

    for (int i = 0; i < numEdges; i++) {
        int u, v, weight;
        scanf("%d %d %d", &u, &v, &weight);
        addEdge(u, v, weight);
    }

    dijkstra(startVertex);

    printf("Vertex\tDistance\n");
    for (int i = 0; i < numVertices; i++) {
        printf("%d\t%d\n", i, dist[i]);
    }

    return 0;
}
// #include <stdio.h>
// #include <stdbool.h>
// #include <limits.h>

// #define MAX_VERTICES 1000
// #define INF 99999

// int graph[MAX_VERTICES][MAX_VERTICES];
// int dist[MAX_VERTICES];
// bool visited[MAX_VERTICES];
// int numVertices;

// void initializeGraph() {
//     for (int i = 0; i < MAX_VERTICES; i++) {
//         for (int j = 0; j < MAX_VERTICES; j++) {
//             graph[i][j] = INF;
//         }
//     }
// }

// void addEdge(int u, int v, int weight) {
//     graph[u][v] = weight;
//     graph[v][u] = weight;
// }

// int findMinDistance() {
//     int minDist = INF;
//     int minIndex = -1;

//     for (int i = 0; i < numVertices; i++) {
//         if (!visited[i] && dist[i] < minDist) {
//             minDist = dist[i];
//             minIndex = i;
//         }
//     }

//     return minIndex;
// }

// void printDijkstraTable(int iteration) {
//     printf("Iteration %d:\n", iteration);
//     printf("Vertex\tDistance\n");
//     for (int i = 0; i < numVertices; i++) {
//         printf("%d\t%d\n", i, dist[i]);
//     }
//     printf("\n");
// }

// void dijkstra(int startVertex) {
//     for (int i = 0; i < numVertices; i++) {
//         dist[i] = INF;
//         visited[i] = false;
//     }

//     dist[startVertex] = 0;

//     for (int count = 0; count < numVertices - 1; count++) {
//         int u = findMinDistance();
//         visited[u] = true;

//         for (int v = 0; v < numVertices; v++) {
//             if (!visited[v] && graph[u][v] != INF && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
//                 dist[v] = dist[u] + graph[u][v];
//             }
//         }

//         printDijkstraTable(count + 1);
//     }
// }

// int main() {
//     int numEdges, startVertex;
//     scanf("%d %d %d", &numVertices, &numEdges, &startVertex);

//     initializeGraph();

//     for (int i = 0; i < numEdges; i++) {
//         int u, v, weight;
//         scanf("%d %d %d", &u, &v, &weight);
//         addEdge(u, v, weight);
//     }

//     dijkstra(startVertex);

//     return 0;
// }

