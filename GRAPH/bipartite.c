#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTICES 100

enum Color {
    RED,
    BLUE,
    UNCOLORED
};

struct Node {
    int vertex;
    struct Node* next;
};

struct Graph {
    struct Node* adjacencyList[MAX_VERTICES];
};

bool isBipartite(struct Graph* graph, int source) {
    enum Color colors[MAX_VERTICES];
    for (int i = 0; i < MAX_VERTICES; i++) {
        colors[i] = UNCOLORED;
    }

    colors[source] = RED;

    struct Node* queue = NULL;
    enqueue(&queue, source);

    while (queue != NULL) {
        int currentVertex = dequeue(&queue);
        struct Node* temp = graph->adjacencyList[currentVertex];

        while (temp != NULL) {
            int neighbor = temp->vertex;

            if (colors[neighbor] == colors[currentVertex]) {
                return false;
            }

            if (colors[neighbor] == UNCOLORED) {
                colors[neighbor] = (colors[currentVertex] == RED) ? BLUE : RED;
                enqueue(&queue, neighbor);
            }

            temp = temp->next;
        }
    }

    return true;
}

void enqueue(struct Node** queue, int vertex) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = vertex;
    newNode->next = NULL;

    if (*queue == NULL) {
        *queue = newNode;
    } else {
        struct Node* temp = *queue;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

int dequeue(struct Node** queue) {
    struct Node* temp = *queue;
    int vertex = temp->vertex;
    *queue = (*queue)->next;
    free(temp);
    return vertex;
}

int main() {
    int V, E;
    printf("Enter the number of vertices: ");
    scanf("%d", &V);
    printf("Enter the number of edges: ");
    scanf("%d", &E);

    struct Graph graph;
    for (int i = 0; i < V; i++) {
        graph.adjacencyList[i] = NULL;
    }

    printf("Enter the edges:\n");
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(&graph, u, v);
    }

    int source;
    printf("Enter the source vertex: ");
    scanf("%d", &source);

    if (isBipartite(&graph, source)) {
        printf("The graph is bipartite.\n");
    } else {
        printf("The graph is not bipartite.\n");
    }

    return 0;
}

void addEdge(struct Graph* graph, int u, int v) {
    struct Node* newNode = createNode(v);
    newNode->next = graph->adjacencyList[u];
    graph->adjacencyList[u] = newNode;

    newNode = createNode(u);
    newNode->next = graph->adjacencyList[v];
    graph->adjacencyList[v] =newNode;

}

struct Node* createNode(int v) {
struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
newNode->vertex = v;
newNode->next = NULL;
return newNode;
}

// In this implementation, we represent the graph using an adjacency list. The `Graph` struct contains an array of linked lists, where each element represents a vertex and its corresponding linked list contains the adjacent vertices.
// The `isBipartite` function takes the graph and the source vertex as input and performs a BFS traversal. It assigns colors (RED and BLUE) to the vertices, starting from the source vertex. If there is any adjacent vertex with the same color as the current vertex, the graph is not bipartite, and the function returns `false`. Otherwise, if all vertices are successfully colored without any violations, the function returns `true`.
// The `enqueue` and `dequeue` functions are used to implement a queue data structure for the BFS traversal.
// In the `main` function, we take input for the number of vertices and edges of the graph, as well as the edges themselves. Then we prompt the user to enter the source vertex. Finally, we call the `isBipartite` function and display whether the graph is bipartite or not.
// Note: Make sure to include the necessary header files (`stdio.h`, `stdbool.h`, `stdlib.h`) and define the required structs (`Node`, `Graph`) before the function implementations.
