// #include <stdio.h>
// #include <stdbool.h>

// #define MAX_SIZE 100

// // Depth-first search function
// void dfs(int graph[MAX_SIZE][MAX_SIZE], int n, int node, bool visited[MAX_SIZE]) {
//     visited[node] = true;
    
//     for (int i = 0; i < n; i++) {
//         if (graph[node][i] && !visited[i]) {
//             dfs(graph, n, i, visited);
//         }
//     }
// }

// // Check if the given order is a valid DFS traversal
// bool isValidDFS(int graph[MAX_SIZE][MAX_SIZE], int n, int order[], int size) {
//     bool visited[MAX_SIZE] = { false };
    
//     // Mark the first node as visited
//     visited[order[0]] = true;
    
//     for (int i = 1; i < size; i++) {
//         int current = order[i];
        
//         if (!visited[current]) {
//             // Check if there is an edge from the previous node to the current node
//             if (!graph[order[i - 1]][current]) {
//                 return false;
//             }
            
//             visited[current] = true;
//         }
//     }
    
//     // Check if all nodes have been visited
//     for (int i = 0; i < n; i++) {
//         if (!visited[i]) {
//             return false;
//         }
//     }
    
//     return true;
// }

// int main() {
//     int n, m; // Number of nodes and edges
//     printf("Enter the number of nodes: ");
//     scanf("%d", &n);
//     printf("Enter the number of edges: ");
//     scanf("%d", &m);
    
//     int graph[MAX_SIZE][MAX_SIZE] = { 0 }; // Adjacency matrix
    
//     printf("Enter the edges:\n");
//     for (int i = 0; i < m; i++) {
//         int u, v;
//         scanf("%d %d", &u, &v);
//         graph[u][v] = 1;
//     }
    
//     int size; // Size of the traversal order
//     printf("Enter the size of the traversal order: ");
//     scanf("%d", &size);
    
//     int order[MAX_SIZE];
//     printf("Enter the traversal order: ");
//     for (int i = 0; i < size; i++) {
//         scanf("%d", &order[i]);
//     }
    
//     if (isValidDFS(graph, n, order, size)) {
//         printf("The given order is a valid DFS traversal.\n");
//     } else {
//         printf("The given order is not a valid DFS traversal.\n");
//     }
    
//     return 0;
// }
#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 26 // Assuming maximum 26 alphabets

// Depth-first search function
void dfs(int graph[MAX_SIZE][MAX_SIZE], int n, int node, bool visited[MAX_SIZE]) {
    visited[node] = true;
    
    for (int i = 0; i < n; i++) {
        if (graph[node][i] && !visited[i]) {
            dfs(graph, n, i, visited);
        }
    }
}

// Check if the given order is a valid DFS traversal
bool isValidDFS(int graph[MAX_SIZE][MAX_SIZE], int n, char order[], int size) {
    bool visited[MAX_SIZE] = { false };
    
    // Mark the first node as visited
    visited[order[0] - 'a'] = true;
    
    for (int i = 1; i < size; i++) {
        int current = order[i] - 'a';
        
        if (!visited[current]) {
            // Check if there is an edge from the previous node to the current node
            if (!graph[order[i - 1] - 'a'][current]) {
                return false;
            }
            
            visited[current] = true;
        }
    }
    
    // Check if all nodes have been visited
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            return false;
        }
    }
    
    return true;
}

int main() {
    int n, m; // Number of nodes and edges
    printf("Enter the number of nodes: ");
    scanf("%d", &n);
    printf("Enter the number of edges: ");
    scanf("%d", &m);
    
    int graph[MAX_SIZE][MAX_SIZE] = { 0 }; // Adjacency matrix
    
    printf("Enter the edges:\n");
    for (int i = 0; i < m; i++) {
        char u, v;
        scanf(" %c %c", &u, &v);
        graph[u - 'a'][v - 'a'] = 1;
    }
    
    int size; // Size of the traversal order
    printf("Enter the size of the traversal order: ");
    scanf("%d", &size);
    
    char order[MAX_SIZE];
    printf("Enter the traversal order: ");
    for (int i = 0; i < size; i++) {
        scanf(" %c", &order[i]);
    }
    
    if (isValidDFS(graph, n, order, size)) {
        printf("The given order is a valid DFS traversal.\n");
    } else {
        printf("The given order is not a valid DFS traversal.\n");
    }
    return 0;
}