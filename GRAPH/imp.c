#include <stdio.h>
#define MAX_VERTICES 100

typedef struct {
    int matrix[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
} Graph;

void bfs(Graph* graph, int startVertex) {
    int visited[MAX_VERTICES] = {0};
    int queue[MAX_VERTICES];
    int front = -1, rear = -1;
    
    visited[startVertex] = 1;
    queue[++rear] = startVertex;
    
    while (front != rear) {
        int currentVertex = queue[++front];
        printf("%d ", currentVertex);
        
        for (int i = 0; i < graph->numVertices; i++) {
            if (graph->matrix[currentVertex][i] == 1 && !visited[i]) {
                queue[++rear] = i;
                visited[i] = 1;
            }
        }
    }
}
void dfs(Graph* graph, int vertex, int visited[]) {
    printf("%d ", vertex);
    visited[vertex] = 1;
    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->matrix[vertex][i] == 1 && !visited[i]) {
            dfs(graph, i, visited);
        }
    }
}
// Dijkstra's Algorithm (Single-Source Shortest Path):
#define INFINITY 9999

void dijkstra(Graph* graph, int source) {
    int dist[MAX_VERTICES];
    int visited[MAX_VERTICES] = {0};
    for (int i = 0; i < graph->numVertices; i++) {
        dist[i] = INFINITY;
    }
    
    dist[source] = 0;
    
    for (int count = 0; count < graph->numVertices - 1; count++) {
        int minDist = INFINITY;
        int minIndex;
        
        for (int i = 0; i < graph->numVertices; i++) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                minIndex = i;
            }
        }
        
        visited[minIndex] = 1;
        
        for (int i = 0; i < graph->numVertices; i++) {
            if (!visited[i] && graph->matrix[minIndex][i] && dist[minIndex] != INFINITY && dist[minIndex] + graph->matrix[minIndex][i] < dist[i]) {
                dist[i] = dist[minIndex] + graph->matrix[minIndex][i];
            }
        }
    }
    
    printf("Vertex\tDistance from Source\n");
    for (int i = 0; i < graph->numVertices; i++) {
        printf("%d\t%d\n", i, dist[i]);
    }
}
int main() {
    Graph graph;
    int numVertices, startVertex;
    
    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);
    
    graph.numVertices = numVertices;
    
    printf("\nEnter the adjacency matrix:\n");
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            scanf("%d", &graph.matrix[i][j]);
        }
    }
    
    printf("\nEnter the starting vertex: ");
    scanf("%d", &startVertex);
    
    printf("\nBreadth-First Search traversal: ");
    bfs(&graph, startVertex);
    
    int visited[MAX_VERTICES] = {0};
    
    printf("\nDepth-First Search traversal: ");
    dfs(&graph, startVertex, visited);

    int source;
    printf("\nEnter the source vertex: ");
    scanf("%d", &source);
    
    dijkstra(&graph, source);
    
    return 0;
}



