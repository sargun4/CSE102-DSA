#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 100
typedef struct {
    int edges[MAX_VERTICES][MAX_VERTICES];
    int vertex_count;
    int edge_count;
} Graph;
// Initialize graph with given number of vertices
void init_graph(Graph *g, int num_vertices) {
    g->vertex_count = num_vertices;
    g->edge_count = 0;
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            g->edges[i][j] = 0;
        }
    }
}
// Add an edge between two vertices in the graph
void add_edge(Graph *g, int vertex1, int vertex2) {
    g->edges[vertex1][vertex2] = 1;
    g->edges[vertex2][vertex1] = 1;
    g->edge_count++;
}
// Remove an edge between two vertices in the graph
void remove_edge(Graph *g, int vertex1, int vertex2) {
    g->edges[vertex1][vertex2] = 0;
    g->edges[vertex2][vertex1] = 0;
    g->edge_count--;
}
// Check if there is an edge between two vertices in the graph
int has_edge(Graph *g, int vertex1, int vertex2) {
    return g->edges[vertex1][vertex2] == 1;
}
void print_graph(Graph *g) {
    printf("Vertices: %d\nEdges: %d\n", g->vertex_count, g->edge_count);
    for (int i = 0; i < g->vertex_count; i++) {
        printf("%d: ", i);
        for (int j = 0; j < g->vertex_count; j++) {
            printf("%d ", g->edges[i][j]);
        }
        printf("\n");
    }
}
int main() {
    Graph g;
    init_graph(&g, 5);
    add_edge(&g, 0, 1);
    add_edge(&g, 1, 2);
    add_edge(&g, 2, 3);
    add_edge(&g, 3, 4);
    print_graph(&g);
    remove_edge(&g, 0, 1);
    print_graph(&g);
    printf("Has edge 2-3: %d\n", has_edge(&g, 2, 3));
    printf("Has edge 0-1: %d\n", has_edge(&g, 0, 1));
    return 0;
}
