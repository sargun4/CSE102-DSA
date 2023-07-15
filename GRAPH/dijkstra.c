
// function Dijkstra(Graph, source):
//        dist[source]  := 0                     // Distance from source to source is set to 0
//        for each vertex v in Graph:            // Initializations
//            if v ≠ source
//                dist[v]  := infinity           // Unknown distance function from source to each node set to infinity
//            add v to Q                         // All nodes initially in Q

//       while Q is not empty:                  // The main loop
//           v := vertex in Q with min dist[v]  // In the first run-through, this vertex is the source node
//           remove v from Q 

//           for each neighbor u of v:           // where neighbor u has not yet been removed from Q.
//               alt := dist[v] + length(v, u)
//               if alt < dist[u]:               // A shorter path to u has been found
//                   dist[u]  := alt            // Update distance of u 

//       return dist[]
//   end function

// // #include <stdio.h>
// // #include <stdbool.h>
// // #include <limits.h>

// // #define MAX_VERTICES 1000
// // #define INF INT_MAX

// // int graph[MAX_VERTICES][MAX_VERTICES];
// // int dist[MAX_VERTICES];
// // bool visited[MAX_VERTICES];
// // int numVertices;

// // void initializeGraph() {
// //     for (int i = 0; i < MAX_VERTICES; i++) {
// //         for (int j = 0; j < MAX_VERTICES; j++) {
// //             graph[i][j] = INF;
// //         }
// //     }
// // }

// // void addEdge(int u, int v, int weight) {
// //     graph[u][v] = weight;
// //     graph[v][u] = weight;
// // }

// // int findMinDistance() {
// //     int minDist = INF;
// //     int minIndex = -1;

// //     for (int i = 0; i < numVertices; i++) {
// //         if (!visited[i] && dist[i] < minDist) {
// //             minDist = dist[i];
// //             minIndex = i;
// //         }
// //     }

// //     return minIndex;
// // }

// // void dijkstra(int startVertex) {
// //     for (int i = 0; i < numVertices; i++) {
// //         dist[i] = INF;
// //         visited[i] = false;
// //     }

// //     dist[startVertex] = 0;

// //     for (int count = 0; count < numVertices - 1; count++) {
// //         int u = findMinDistance();
// //         visited[u] = true;

// //         for (int v = 0; v < numVertices; v++) {
// //             if (!visited[v] && graph[u][v] != INF && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
// //                 dist[v] = dist[u] + graph[u][v];
// //             }
// //         }
// //     }
// // }

// // int main() {
// //     int numEdges, startVertex;
// //     scanf("%d %d %d", &numVertices, &numEdges, &startVertex);

// //     initializeGraph();

// //     for (int i = 0; i < numEdges; i++) {
// //         int u, v, weight;
// //         scanf("%d %d %d", &u, &v, &weight);
// //         addEdge(u, v, weight);
// //     }

// //     dijkstra(startVertex);

// //     printf("Vertex\tDistance\n");
// //     for (int i = 0; i < numVertices; i++) {
// //         printf("%d\t%d\n", i, dist[i]);
// //     }

// //     return 0;
// // }
// #include <stdio.h>
// #include <stdbool.h>
// #include <limits.h>

// #define MAX_VERTICES 1000
// #define INF 99999

// int graph[MAX_VERTICES][MAX_VERTICES];
// int dist[MAX_VERTICES];
// bool visited[MAX_VERTICES];
// int numVertices;

// void initializeGraph() {
//     for (int i = 0; i < MAX_VERTICES; i++) {
//         for (int j = 0; j < MAX_VERTICES; j++) {
//             graph[i][j] = INF;
//         }
//     }
// }

// void addEdge(int u, int v, int weight) {
//     graph[u][v] = weight;
//     graph[v][u] = weight;
// }

// int findMinDistance() {
//     int minDist = INF;
//     int minIndex = -1;

//     for (int i = 0; i < numVertices; i++) {
//         if (!visited[i] && dist[i] < minDist) {
//             minDist = dist[i];
//             minIndex = i;
//         }
//     }

//     return minIndex;
// }

// void printDijkstraTable(int iteration) {
//     printf("Iteration %d:\n", iteration);
//     printf("Vertex\tDistance\n");
//     for (int i = 0; i < numVertices; i++) {
//         printf("%d\t%d\n", i, dist[i]);
//     }
//     printf("\n");
// }

// void dijkstra(int startVertex) {
//     for (int i = 0; i < numVertices; i++) {
//         dist[i] = INF;
//         visited[i] = false;
//     }

//     dist[startVertex] = 0;

//     for (int count = 0; count < numVertices - 1; count++) {
//         int u = findMinDistance();
//         visited[u] = true;

//         for (int v = 0; v < numVertices; v++) {
//             if (!visited[v] && graph[u][v] != INF && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
//                 dist[v] = dist[u] + graph[u][v];
//             }
//         }

//         printDijkstraTable(count + 1);
//     }
// }

// int main() {
//     int numEdges, startVertex;
//     scanf("%d %d %d", &numVertices, &numEdges, &startVertex);

//     initializeGraph();

//     for (int i = 0; i < numEdges; i++) {
//         int u, v, weight;
//         scanf("%d %d %d", &u, &v, &weight);
//         addEdge(u, v, weight);
//     }

//     dijkstra(startVertex);

//     return 0;
// }




#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define V 12

struct Node {
    int vertex;
    int weight;
    struct Node* next;
};

struct Graph {
    struct Node** adjacency_list;
};

struct Node* create_node(int vertex, int weight) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

struct Graph* create_graph() {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->adjacency_list = (struct Node**)malloc(V * sizeof(struct Node*));
    for (int i = 0; i < V; i++) {
        graph->adjacency_list[i] = NULL;
    }
    return graph;
}

void add_edge(struct Graph* graph, int src, int dest, int weight) {
    struct Node* newNode = create_node(dest, weight);
    newNode->next = graph->adjacency_list[src];
    graph->adjacency_list[src] = newNode;

    newNode = create_node(src, weight);
    newNode->next = graph->adjacency_list[dest];
    graph->adjacency_list[dest] = newNode;
}

int min_distance(int distance[], bool visited[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++) {
        if (visited[v] == false && distance[v] <= min) {
            min = distance[v];
            min_index = v;
        }
    }
    return min_index;
}

void print_path(int parent[], int j) {
    if (parent[j] == -1) {
        printf("%d ", j);
        return;
    }
    print_path(parent, parent[j]);
    printf("%d ", j);
}

void print_solution(int distance[], int parent[], int src) {
    printf("Vertex\t  Distance\tPath");
    for (int i = 0; i < V; i++) {
        if (i != src) {
            printf("\n%d -> %d \t\t%d\t%d ", src, i, distance[i], src);
            print_path(parent, i);
        }
    }
    printf("\n");
}

void dijkstra(struct Graph* graph, int src) {
    int distance[V]; // Array to store the shortest distance from source to each vertex
    bool visited[V]; // Array to track visited vertices
    int parent[V];   // Array to store the parent vertex in the shortest path

    // Initialize distance, visited, and parent arrays
    for (int i = 0; i < V; i++) {
        distance[i] = INT_MAX;
        visited[i] = false;
        parent[i] = -1;
    }

    // Distance from source vertex to itself is 0
    distance[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Find the vertex with the minimum distance value
        int u = min_distance(distance, visited);

        // Mark the selected vertex as visited
        visited[u] = true;

        // Update distance value of adjacent vertices
        struct Node* temp = graph->adjacency_list[u];
        while (temp != NULL) {
            int v = temp->vertex;
            int weight = temp->weight;
            if (visited[v] == false && distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                parent[v] = u;
            }
            temp = temp->next;
        }
    }

    // Print the shortest paths and distances
    print_solution(distance, parent, src);
}

int main() {
    struct Graph* graph = create_graph();

    // Add edges to the graph
    add_edge(graph,0,1,3);
    add_edge(graph,0,3,4);
    add_edge(graph,0,2,5);
    add_edge(graph,1,4,3);
    add_edge(graph,1,5,6);
    add_edge(graph,1,0,3);
    add_edge(graph,2,0,5);
    add_edge(graph,2,3,2);
    add_edge(graph,2,6,4);
    add_edge(graph,3,0,4);
    add_edge(graph,3,4,1);
    add_edge(graph,3,2,2);
    add_edge(graph,3,7,5);
    add_edge(graph,4,1,3);
    add_edge(graph,4,3,1);
    add_edge(graph,4,5,2);
    add_edge(graph,4,8,4);
    add_edge(graph,5,4,2);
    add_edge(graph,5,1,6);
    add_edge(graph,5,9,5);
    add_edge(graph,6,2,4);
    add_edge(graph,6,7,3);
    add_edge(graph,6,10,6);
    add_edge(graph,7,8,6);
    add_edge(graph,7,3,5);
    add_edge(graph,7,6,3);
    add_edge(graph,7,10,7);
    add_edge(graph,8,7,6);
    add_edge(graph,8,4,4);
    add_edge(graph,8,9,3);
    add_edge(graph,8,11,5);
    add_edge(graph,9,5,5);
    add_edge(graph,9,8,3);
    add_edge(graph,9,11,9);
    add_edge(graph,10,6,6);
    add_edge(graph,10,7,7);
    add_edge(graph,10,11,8);
    add_edge(graph,11,10,8);
    add_edge(graph,11,8,5);
    add_edge(graph,11,9,9);
    int source_vertex = 0;
    dijkstra(graph, source_vertex);
    return 0;
}


// undircted 
// 12 20 0
// 0 1 3
// 0 3 4
// 0 2 5
// 1 4 3
// 1 5 6
// 1 0 3
// 2 0 5
// 2 3 2
// 2 6 4
// 3 0 4
// 3 4 1
// 3 2 2
// 3 7 5
// 4 1 3
// 4 3 1
// 4 5 2
// 4 8 4
// 5 4 2
// 5 1 6
// 5 9 5
// 6 2 4
// 6 7 3
// 6 10 6
// 7 8 6
// 7 3 5
// 7 6 3
// 7 10 7
// 8 7 6
// 8 4 4
// 8 9 3
// 8 11 5
// 9 5 5
// 9 8 3
// 9 11 9
// 10 6 6
// 10 7 7
// 10 11 8
// 11 10 8
// 11 8 5
// 11 9 9

