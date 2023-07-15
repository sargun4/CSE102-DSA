#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

enum Color { WHITE, GRAY, BLACK };

struct Node {
    int vertex;
    struct Node* next;
};

struct Graph {
    struct Node* adjList[MAX_VERTICES];
};

void enqueue(int* queue, int* rear, int item) {
    queue[++(*rear)] = item;
}

int dequeue(int* queue, int* front) {
    return queue[++(*front)];
}

void BFS(struct Graph* graph, int source) {
    enum Color color[MAX_VERTICES];
    int distance[MAX_VERTICES];
    int predecessor[MAX_VERTICES];
    int queue[MAX_VERTICES];
    int front = -1, rear = -1;

    for (int u = 0; u < MAX_VERTICES; u++) {
        if (u != source) {
            color[u] = WHITE;
            distance[u] = -1;
            predecessor[u] = -1;
        }
    }

    color[source] = GRAY;
    distance[source] = 0;
    predecessor[source] = -1;
    enqueue(queue, &rear, source);

    while (front != rear) {
        int u = dequeue(queue, &front);
        struct Node* temp = graph->adjList[u];

        while (temp != NULL) {
            int v = temp->vertex;

            if (color[v] == WHITE) {
                color[v] = GRAY;
                distance[v] = distance[u] + 1;
                predecessor[v] = u;
                enqueue(queue, &rear, v);
            }

            temp = temp->next;
        }

        color[u] = BLACK;
    }

    // Print the results
    printf("Vertex\tDistance\tPredecessor\n");
    for (int v = 0; v < MAX_VERTICES; v++) {
        printf("%d\t%d\t\t%d\n", v, distance[v], predecessor[v]);
    }
}

int main() {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));

    // Initialize the adjacency list
    for (int i = 0; i < MAX_VERTICES; i++) {
        graph->adjList[i] = NULL;
    }

    // TODO: Build the graph by adding edges to the adjacency list

    int source;
    printf("Enter the source vertex: ");
    scanf("%d", &source);

    // Perform BFS from the source vertex
    BFS(graph, source);

    return 0;
}
