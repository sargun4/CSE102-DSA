#include <stdio.h>
#define MAX_VERTICES 100
#define INFINITY 9999

typedef struct {
    int source;
    int destination;
    int weight;
} Edge;

typedef struct {
    Edge edges[MAX_VERTICES * MAX_VERTICES];
    int numVertices;
    int numEdges;
} Graph;

void bellmanFord(Graph* graph, int source) {
    int distance[MAX_VERTICES];
    
    for (int i = 0; i < graph->numVertices; i++) {
        distance[i] = INFINITY;
    }
    
    distance[source] = 0;
    
    for (int i = 0; i < graph->numVertices - 1; i++) {
        for (int j = 0; j < graph->numEdges; j++) {
            int u = graph->edges[j].source;
            int v = graph->edges[j].destination;
            int weight = graph->edges[j].weight;
            
            if (distance[u] != INFINITY && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
            }
        }
    }
    
    // Check for negative weight cycles
    for (int i = 0; i < graph->numEdges; i++) {
        int u = graph->edges[i].source;
        int v = graph->edges[i].destination;
        int weight = graph->edges[i].weight;
        
        if (distance[u] != INFINITY && distance[u] + weight < distance[v]) {
            printf("Graph contains a negative weight cycle\n");
            return;
        }
    }
    
    printf("Vertex\tDistance from Source\n");
    for (int i = 0; i < graph->numVertices; i++) {
        printf("%d\t%d\n", i, distance[i]);
    }
}

int main() {
    Graph graph;
    int numVertices, numEdges, source;
    
    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);
    
    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);
    
    graph.numVertices = numVertices;
    graph.numEdges = numEdges;
    
    printf("\nEnter the edges (source destination weight):\n");
    for (int i = 0; i < numEdges; i++) {
        scanf("%d %d %d", &graph.edges[i].source, &graph.edges[i].destination, &graph.edges[i].weight);
    }
    
    printf("\nEnter the source vertex: ");
    scanf("%d", &source);
    
    bellmanFord(&graph, source);
    
    return 0;
}
