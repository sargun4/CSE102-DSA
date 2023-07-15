#include <stdio.h>
#define MAX_VERTICES 100
#define INFINITY 9999

typedef struct {
    int matrix[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
} Graph;

void primMST(Graph* graph) {
    int parent[MAX_VERTICES];
    int key[MAX_VERTICES];
    int visited[MAX_VERTICES] = {0};
    
    for (int i = 0; i < graph->numVertices; i++) {
        key[i] = INFINITY;
    }
    
    key[0] = 0;
    parent[0] = -1;
    
    for (int count = 0; count < graph->numVertices - 1; count++) {
        int minKey = INFINITY;
        int minIndex;
        
        for (int i = 0; i < graph->numVertices; i++) {
            if (!visited[i] && key[i] < minKey) {
                minKey = key[i];
                minIndex = i;
            }
        }
        
        visited[minIndex] = 1;
        
        for (int i = 0; i < graph->numVertices; i++) {
            if (graph->matrix[minIndex][i] && !visited[i] && graph->matrix[minIndex][i] < key[i]) {
                parent[i] = minIndex;
                key[i] = graph->matrix[minIndex][i];
            }
        }
    }
    
    printf("Edge\tWeight\n");
    for (int i = 1; i < graph->numVertices; i++) {
        printf("%d - %d\t%d\n", parent[i], i, graph->matrix[i][parent[i]]);
    }
}

int main() {
    Graph graph;
    int numVertices;
    
    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);
    
    graph.numVertices = numVertices;
    
    printf("\nEnter the adjacency matrix:\n");
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            scanf("%d", &graph.matrix[i][j]);
        }
    }
    
    primMST(&graph);
    
    return 0;
}
#include <stdio.h>
#define MAX_EDGES 100
#define MAX_VERTICES 100

typedef struct {
    int u;
    int v;
    int weight;
} Edge;

typedef struct {
    Edge edges[MAX_EDGES];
    int numEdges;
} Graph;

void swap(Edge* a, Edge* b) {
    Edge temp = *a;
    *a = *b;
    *b = temp;
}

void sortEdges(Graph* graph) {
    for (int i = 0; i < graph->numEdges - 1; i++) {
        for (int j = 0; j < graph->numEdges - i - 1; j++) {
            if (graph->edges[j].weight > graph->edges[j + 1].weight) {
                swap(&graph->edges[j], &graph->edges[j + 1]);
            }
        }
    }
}

int find(int parent[], int vertex) {
    if (parent[vertex] == vertex) {
        return vertex;
    }
    
    return find(parent, parent[vertex]);
}

void unionSet(int parent[], int rank[], int x, int y) {
    int xRoot = find(parent, x);
    int yRoot = find(parent, y);
    
    if (rank[xRoot] < rank[yRoot]) {
        parent[xRoot] = yRoot;
    } else if (rank[xRoot] > rank[yRoot]) {
        parent[yRoot] = xRoot;
    } else {
        parent[yRoot] = xRoot;
        rank[xRoot]++;
    }
}

void kruskalMST(Graph* graph) {
    Edge result[MAX_EDGES];
    int parent[MAX_VERTICES];
    int rank[MAX_VERTICES] = {0};
    
    sortEdges(graph);
    
    for (int i = 0; i < graph->numEdges; i++) {
        parent[i] = i;
    }
    
    int count = 0;
    int index = 0;
    
    while (count < graph->numVertices - 1) {
        Edge currentEdge = graph->edges[index++];
        
        int uRoot = find(parent, currentEdge.u);
        int vRoot = find(parent, currentEdge.v);
        
        if (uRoot != vRoot) {
            result[count++] = currentEdge;
            unionSet(parent, rank, uRoot, vRoot);
        }
    }
    
    printf("Edge\tWeight\n");
    for (int i = 0; i < count; i++) {
        printf("%d - %d\t%d\n", result[i].u, result[i].v, result[i].weight);
    }
}

int main() {
    Graph graph;
    int numVertices, numEdges;
    
    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);
    
    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);
    
    graph.numEdges = numEdges;
    
    printf("\nEnter the edges (u v weight):\n");
    for (int i = 0; i < numEdges; i++) {
        scanf("%d %d %d", &graph.edges[i].u, &graph.edges[i].v, &graph.edges[i].weight);
    }
    
    kruskalMST(&graph);
    
    return 0;
}
