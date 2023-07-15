// #include <stdio.h>
// #include <stdlib.h>
// #define MAX_ROOMS 100000
// struct node {
//     int destination;
//     struct node* next;
// };

// struct node* createnode(int destination) {
//     struct node* temp = (struct node*)malloc(sizeof(struct node));
//     temp->destination = destination;
//     temp->next = NULL;
//     return temp;
// }
// struct graph {
//     int no_vertices;
//     struct node** adjlist;
// };
// struct graph* creategraph(int no_vertices) {
//     struct graph* g = (struct graph*)malloc(sizeof(struct graph));
//     g->no_vertices = no_vertices;

//     g->adjlist = (struct node**)malloc(no_vertices * sizeof(struct node*));
//     for (int i = 0; i < no_vertices; i++) {
//         g->adjlist[i] = NULL;
//     }

//     return g;
// }

// void addedge(struct graph* g, int src, int dest) {
//     struct node* temp = createnode(dest);
//     temp->next = g->adjlist[src];
//     g->adjlist[src] = temp;
// }

// void DFS(struct graph* g, int vertex, int* visited, int* stack, int* stackIndex) {
//     visited[vertex] = 1;
//     struct node* temp = g->adjlist[vertex];
//     while (temp != NULL) {
//         if (!visited[temp->destination]) {
//             DFS(g, temp->destination, visited, stack, stackIndex);
//         }
//         temp = temp->next;
//     }

//     stack[(*stackIndex)++] = vertex;
// }

// struct graph* transpose_grph(struct graph* g) {
//     struct graph* transposedGraph = creategraph(g->no_vertices);

//     for (int vertex = 0; vertex < g->no_vertices; vertex++) {
//         struct node* temp = g->adjlist[vertex];
//         while (temp != NULL) {
//             addedge(transposedGraph, temp->destination, vertex);
//             temp = temp->next;
//         }
//     }

//     return transposedGraph;
// }
// int is_stronglyconnected(struct graph* g) {
//     int visited[MAX_ROOMS] = {0};
//     int stack[MAX_ROOMS];
//     int stackIndex = 0;
//     DFS(g, 0, visited, stack, &stackIndex);
//     for (int vertex = 0; vertex < g->no_vertices; vertex++) {
//         if (!visited[vertex]) {
//             return 0;  // graph is not strongly connected
//         }
//     }
//     struct graph* transposedGraph = transpose_grph(g);
//     for (int i = 0; i < g->no_vertices; i++) {
//         visited[i] = 0;
//     }
//     stackIndex = 0;
//     DFS(transposedGraph, 0, visited, stack, &stackIndex);
//     // tochrck if all vertices are visited after transposing
//     for (int vertex = 0; vertex < transposedGraph->no_vertices; vertex++) {
//         if (!visited[vertex]) {
//             return 0;  // graph is not strongly connected
//         }
//     }

//     return 1;  // graph is strongly connected
// }
// void freeGraph(struct graph* g) {
//     for (int i = 0; i < g->no_vertices; i++) {
//         struct node* temp = g->adjlist[i];
//         while (temp != NULL) {
//             struct node* prev = temp;
//             temp = temp->next;
//             free(prev);
//         }
//     }

//     free(g->adjlist);
//     free(g);
// }
// int main() {
//     int rooms, tunnels;
//     scanf("%d %d", &rooms, &tunnels);
//     struct graph* g = creategraph(rooms);

//     for (int i = 0; i < tunnels; i++) {
//         int src, dest;
//         scanf("%d %d", &src, &dest);
//         addedge(g, src - 1, dest - 1);  
//         addedge(g, dest - 1, src - 1); 
//     }
//     if (is_stronglyconnected(g))  printf("NO\n");
//     else  printf("YES\n");
//     freeGraph(g);
//     return 0;
// }


// Create a directed graph using the given inputs, where each room is represented by a vertex and each tunnel is represented by a directed edge between two vertices.

// Run a DFS from an arbitrary vertex to visit all reachable vertices. Keep track of the visited vertices during the DFS.

// If the DFS visit covers all vertices (i.e., the visited set contains all vertices), continue to the next step. Otherwise, output "NO" since it is not possible to make each room reachable from every other room.

// Reverse the directions of all edges in the graph to make each tunnel one-way.

// Run another DFS from the same arbitrary vertex as in step 2 to visit all reachable vertices. Again, keep track of the visited vertices.

// If the DFS visit covers all vertices, output "YES" since it is possible to make each room reachable from every other room. Otherwise, output "NO" since there exists a room that is not reachable from every other room.
#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTICES 100001
#define MAX_EDGES 200001

typedef struct {
    int vertices;
    int edges;
    int graph[MAX_VERTICES][2];
} Labyrinth;

void initializeLabyrinth(Labyrinth* labyrinth) {
    labyrinth->vertices = 0;
    labyrinth->edges = 0;
}

void addTunnel(Labyrinth* labyrinth, int x, int y) {
    labyrinth->graph[labyrinth->edges][0] = x;
    labyrinth->graph[labyrinth->edges][1] = y;
    labyrinth->edges++;
}

bool isStronglyConnected(Labyrinth* labyrinth) {
    int numVertices = labyrinth->vertices;
    int numEdges = labyrinth->edges;
    int graph[MAX_VERTICES][2] = {0};
    for (int i = 0; i < numEdges; i++) {
        int x = labyrinth->graph[i][0];
        int y = labyrinth->graph[i][1];
        graph[x][0]++;
        graph[y][1]++;
    }
    for (int i = 1; i <= numVertices; i++) {
        if (graph[i][0] == 0 || graph[i][1] == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    Labyrinth labyrinth;
    initializeLabyrinth(&labyrinth);
    int numVertices, numEdges;
    scanf("%d %d", &numVertices, &numEdges);
    labyrinth.vertices = numVertices;
    for (int i = 0; i < numEdges; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        addTunnel(&labyrinth, x, y);
        addTunnel(&labyrinth, y, x);
    }
    if (isStronglyConnected(&labyrinth)) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
    return 0;
}
