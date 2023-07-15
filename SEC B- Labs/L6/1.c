#include <stdio.h>
#include <stdlib.h>

#define MAX_ROOMS 100000

// node structure for adjacency list representation
struct node {
    int destination;
    struct node* next;
};

struct node* createnode(int destination) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->destination = destination;
    temp->next = NULL;
    return temp;
}

struct graph {
    int no_vertices;
    struct node** adjlist;
};
struct graph* creategraph(int no_vertices) {
    struct graph* g = (struct graph*)malloc(sizeof(struct graph));
    g->no_vertices = no_vertices;

    g->adjlist = (struct node**)malloc(no_vertices * sizeof(struct node*));
    for (int i = 0; i < no_vertices; i++) {
        g->adjlist[i] = NULL;
    }

    return g;
}

void addedge(struct graph* g, int src, int dest) {
    struct node* temp = createnode(dest);
    temp->next = g->adjlist[src];
    g->adjlist[src] = temp;
}

void DFS(struct graph* g, int vertex, int* visited, int* stack, int* stackIndex) {
    visited[vertex] = 1;
    struct node* temp = g->adjlist[vertex];
    while (temp != NULL) {
        if (!visited[temp->destination]) {
            DFS(g, temp->destination, visited, stack, stackIndex);
        }
        temp = temp->next;
    }

    stack[(*stackIndex)++] = vertex;
}

struct graph* transpose_grph(struct graph* g) {
    struct graph* transposedGraph = creategraph(g->no_vertices);

    for (int vertex = 0; vertex < g->no_vertices; vertex++) {
        struct node* temp = g->adjlist[vertex];
        while (temp != NULL) {
            addedge(transposedGraph, temp->destination, vertex);
            temp = temp->next;
        }
    }

    return transposedGraph;
}

// Function to check if the g is strongly connected
int is_stronglyconnected(struct graph* g) {
    int visited[MAX_ROOMS] = {0};
    int stack[MAX_ROOMS];
    int stackIndex = 0;

    DFS(g, 0, visited, stack, &stackIndex);

    // Check if all vertices are visited
    for (int vertex = 0; vertex < g->no_vertices; vertex++) {
        if (!visited[vertex]) {
            return 0;  // graph is not strongly connected
        }
    }

    struct graph* transposedGraph = transpose_grph(g);
    for (int i = 0; i < g->no_vertices; i++) {
        visited[i] = 0;
    }
    stackIndex = 0;

    DFS(transposedGraph, 0, visited, stack, &stackIndex);

    // Check if all vertices are visited after transposing
    for (int vertex = 0; vertex < transposedGraph->no_vertices; vertex++) {
        if (!visited[vertex]) {
            return 0;  // graph is not strongly connected
        }
    }

    return 1;  // graph is strongly connected
}

// Function to free the memory allocated for the g
void freeGraph(struct graph* g) {
    for (int i = 0; i < g->no_vertices; i++) {
        struct node* temp = g->adjlist[i];
        while (temp != NULL) {
            struct node* prev = temp;
            temp = temp->next;
            free(prev);
        }
    }

    free(g->adjlist);
    free(g);
}

int main() {
    int numRooms, numTunnels;
    scanf("%d %d", &numRooms, &numTunnels);

    struct graph* g = creategraph(numRooms);

    for (int i = 0; i < numTunnels; i++) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        addedge(g, src - 1, dest - 1);  // Adjusting indices to 0-based
        addedge(g, dest - 1, src - 1);  // Adding both directions
    }

    if (is_stronglyconnected(g)) {
        printf("NO\n");
    } else {
        printf("YES\n");
    }

    freeGraph(g);

    return 0;
}
