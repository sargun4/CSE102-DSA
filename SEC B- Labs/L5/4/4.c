// Create a 2D matrix of size m x n to represent the land and initialize all cells with "infinity."
// Read the matrix values from input.
// Create a queue to perform BFS.
// Iterate through the boundary cells of the land (cells at the edges).
// If the cell contains a normal plant (value is 0), set its time value to 0 and enqueue it.
// Perform BFS until the queue is empty.
// Dequeue a cell from the queue.
// Check the neighboring cells (up, down, left, right).
// If the neighboring cell is within the boundaries and has a value of "infinity" (meaning it hasn't been visited yet), and it contains a normal plant (value is 0), set its time value to the current cell's time value plus 1, and enqueue it.
// Read the number of queries, q.
// For each query, read the position of the plant (x, y).
// If the cell at position (x, y) has a value of "infinity," print "infinity."
// Otherwise, print the time value of the cell at position (x, y).
// Repeat step 8 for all queries.
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000
#define INF 1e9

typedef struct {
    int row;
    int col;
} Cell;

int land[MAX_SIZE][MAX_SIZE];
int timeToReach[MAX_SIZE][MAX_SIZE];
int visited[MAX_SIZE][MAX_SIZE];
int m, n;

int isValidCell(int row, int col) {
    return row >= 0 && row < m && col >= 0 && col < n;
}

void BFS() {
    Cell* queue = (Cell*)malloc(m * n * sizeof(Cell));
    int front = 0;
    int rear = 0;

    // Enqueue the boundary cells with normal plants (value is 0)
    for (int i = 0; i < m; i++) {
        if (land[i][0] == 0) {
            queue[rear].row = i;
            queue[rear].col = 0;
            timeToReach[i][0] = 0;
            visited[i][0] = 1;
            rear++;
        }
        if (land[i][n - 1] == 0) {
            queue[rear].row = i;
            queue[rear].col = n - 1;
            timeToReach[i][n - 1] = 0;
            visited[i][n - 1] = 1;
            rear++;
        }
    }
    for (int j = 1; j < n - 1; j++) {
        if (land[0][j] == 0) {
            queue[rear].row = 0;
            queue[rear].col = j;
            timeToReach[0][j] = 0;
            visited[0][j] = 1;
            rear++;
        }
        if (land[m - 1][j] == 0) {
            queue[rear].row = m - 1;
            queue[rear].col = j;
            timeToReach[m - 1][j] = 0;
            visited[m - 1][j] = 1;
            rear++;
        }
    }

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    // Perform BFS
    while (front < rear) {
        Cell current = queue[front];
        front++;

        for (int i = 0; i < 4; i++) {
            int newRow = current.row + dr[i];
            int newCol = current.col + dc[i];

            if (isValidCell(newRow, newCol) && !visited[newRow][newCol] && land[newRow][newCol] == 0) {
                timeToReach[newRow][newCol] = timeToReach[current.row][current.col] + 1;
                visited[newRow][newCol] = 1;
                queue[rear].row = newRow;
                queue[rear].col = newCol;
                rear++;
            }
        }
    }

    free(queue);
}

int main() {
    scanf("%d %d", &m, &n);

    // Read the land matrix
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &land[i][j]);
            timeToReach[i][j] = INF;
            visited[i][j] = 0;
        }
    }

    // Perform BFS to calculate the time to reach each cell
    BFS();

    int q;
    scanf("%d", &q);

    // Answer the queries
    while (q--) {
        int x, y;
        scanf("%d %d", &x, &y);

        if (timeToReach[x][y] == INF) {
            printf("infinity\n");
        } else {
            printf("%d\n", timeToReach[x][y]+1);
        }
    }

    return 0;
}
