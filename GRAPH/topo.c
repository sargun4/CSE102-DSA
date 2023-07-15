// wrong 
// #include <stdio.h>
// #define MAX_VERTICES 100

// typedef struct {
//     int matrix[MAX_VERTICES][MAX_VERTICES];
//     int numVertices;
// } Graph;

// void topologicalSortDFS(Graph* graph, int vertex, int visited[], int stack[]) {
//     visited[vertex] = 1;
    
//     for (int i = 0; i < graph->numVertices; i++) {
//         if (graph->matrix[vertex][i] && !visited[i]) {
//             topologicalSortDFS(graph, i, visited, stack);
//         }
//     }
    
//     stack[--stack[0]] = vertex;
// }

// void topologicalSort(Graph* graph) {
//     int visited[MAX_VERTICES] = {0};
//     int stack[MAX_VERTICES + 1];
    
//     stack[0] = graph->numVertices;
    
//     for (int i = 0; i < graph->numVertices; i++) {
//         if (!visited[i]) {
//             topologicalSortDFS(graph, i, visited, stack);
//         }
//     }
    
//     printf("Topological Sort: ");
//     for (int i = 1; i <= graph->numVertices; i++) {
//         printf("%d ", stack[i]);
//     }
// }

// int main() {
//     Graph graph;
//     int numVertices;
    
//     printf("Enter the number of vertices: ");
//     scanf("%d", &numVertices);
    
//     graph.numVertices = numVertices;
    
//     printf("\nEnter the adjacency matrix:\n");
//     for (int i = 0; i < numVertices; i++) {
//         for (int j = 0; j < numVertices; j++) {
//             scanf("%d", &graph.matrix[i][j]);
//         }
//     }
    
//     topologicalSort(&graph);
    
//     return 0;
// }
