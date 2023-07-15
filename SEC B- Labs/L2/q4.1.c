// Approach:
// Since the fire can spread from one house to every house touching that house, we can think of this problem as a graph problem.
// We can represent each house as a node in the graph and if two houses are adjacent to each other, then there will be an edge between them.
// We can start from the houses where the fire started and do a breadth-first search to determine the time it takes for the fire to reach each house.
// We can keep track of the maximum time it takes for the fire to reach any house, which will be the answer.
// Algorithm:
// Read the values of m and n
// Read the binary 2D matrix and create a graph from it.
// Initialize a queue to perform breadth-first search.
// For each starting point of the fire, add it to the queue with a time of 0.
// Perform breadth-first search until the queue is empty.
// For each node visited, update its time if the current time is less than the previous time or if it has not been visited before.
// Keep track of the maximum time for any node visited.
// Output the maximum time.
// Time Complexity: O(m*n) since we are visiting each node only once.
#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 10005

int m, n;
int matrix[MAX_SIZE][MAX_SIZE];
bool visited[MAX_SIZE][MAX_SIZE];
int max_time = 0;

// Structure to represent a node in the graph
typedef struct {
    int x;
    int y;
    int time;
} Node;

// Utility function to check if a given cell is a valid cell in the matrix
bool isValid(int x, int y) {
    return (x >= 0 && x < m && y >= 0 && y < n);
}

// Function to perform breadth-first search
void bfs(int x, int y) {
    // Initialize the queue
    Node queue[MAX_SIZE*MAX_SIZE];
    int front = 0;
    int rear = 0;

    // Add the starting node to the queue
    queue[rear++] = (Node){x, y, 0};
    visited[x][y] = true;

    // Perform breadth-first search
    while (front < rear) {
        // Dequeue a node from the queue
        Node node = queue[front++];

        // Update the maximum time
        if (node.time > max_time) {
            max_time = node.time;
        }

        // Check all adjacent nodes
        int dx[] = {-1, 0, 1, 0};
        int dy[] = {0, 1, 0, -1};
        for (int i = 0; i < 4; i++) {
            int new_x = node.x + dx[i];
            int new_y = node.y + dy[i];

            // Check if the adjacent node is a valid node and has not been visited yet
            if (isValid(new_x, new_y) && !visited[new_x][new_y]) {
                // Add the adjacent node to the queue with the updated time
                queue[rear++] = (Node){new_x, new_y, node.time+1};
                visited[new_x][new_y] = true;
            }
        }
    }
}

int main() {
    // Read the values of m and n
    scanf("%d%d", &m, &n);
    // Read the binary 2D matrix
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    // Perform breadth-first search from the starting points of the fire
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 1) {
                bfs(i, j);
            }
        }
    }
    printf("%d\n", max_time);
    return 0;
}
