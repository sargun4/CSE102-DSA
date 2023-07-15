#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// Stack implementation for storing the sorted vertices
typedef struct {
    int arr[MAX_VERTICES];
    int top;
} Stack;

void initializeStack(Stack* stack) {
    stack->top = -1;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

void push(Stack* stack, int vertex) {
    stack->arr[++stack->top] = vertex;
}

int pop(Stack* stack) {
    return stack->arr[stack->top--];
}

// Depth-first search to perform topological sort
void dfsTopologicalSort(int vertex, int visited[], int adjacencyMatrix[][MAX_VERTICES], Stack* stack, int numVertices) {
    int i;

    visited[vertex] = 1;

    for (i = 0; i < numVertices; i++) {
        if (adjacencyMatrix[vertex][i] && !visited[i]) {
            dfsTopologicalSort(i, visited, adjacencyMatrix, stack, numVertices);
        }
    }

    push(stack, vertex);
}

void topologicalSort(int adjacencyMatrix[][MAX_VERTICES], int numVertices) {
    int visited[MAX_VERTICES];
    Stack stack;
    int i;

    initializeStack(&stack);

    for (i = 0; i < numVertices; i++) {
        visited[i] = 0;
    }

    for (i = 0; i < numVertices; i++) {
        if (!visited[i]) {
            dfsTopologicalSort(i, visited, adjacencyMatrix, &stack, numVertices);
        }
    }

    printf("Topological Sorting: ");
    while (!isEmpty(&stack)) {
        printf("%d ", pop(&stack));
    }
    printf("\n");
}

int main() {
    int numVertices, i, j;
    int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES];

    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);

    printf("Enter the adjacency matrix:\n");
    for (i = 0; i < numVertices; i++) {
        for (j = 0; j < numVertices; j++) {
            scanf("%d", &adjacencyMatrix[i][j]);
        }
    }
    topologicalSort(adjacencyMatrix, numVertices);
    return 0;
}
