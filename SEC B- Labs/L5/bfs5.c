// #include <stdio.h>
// #include <stdbool.h>

// #define MAX_SIZE 100

// // Structure to represent a cell in the matrix
// typedef struct {
//     int row;
//     int col;
// } Cell;

// // Function to check if a cell is valid and not visited
// bool isValidCell(int row, int col, int numRows, int numCols, bool visited[][MAX_SIZE]) {
//     return (row >= 0 && row < numRows && col >= 0 && col < numCols && !visited[row][col]);
// }

// // Function to perform breadth-first search
// void bfs(int matrix[][MAX_SIZE], int numRows, int numCols, int startRow, int startCol) {
//     bool visited[MAX_SIZE][MAX_SIZE] = {false};
//     Cell queue[MAX_SIZE * MAX_SIZE];
//     int front = 0, rear = 0;

//     // Directions for exploring adjacent cells
//     int dr[] = {-1, 0, 1, 0};
//     int dc[] = {0, 1, 0, -1};

//     // Mark the starting cell as visited and enqueue it
//     visited[startRow][startCol] = true;
//     queue[rear].row = startRow;
//     queue[rear].col = startCol;
//     rear++;

//     printf("BFS Traversal: ");

//     while (front != rear) {
//         Cell currentCell = queue[front++];
//         int currentRow = currentCell.row;
//         int currentCol = currentCell.col;

//         printf("(%d, %d) ", currentRow, currentCol);

//         // Explore all adjacent cells of the current cell
//         for (int i = 0; i < 4; i++) {
//             int newRow = currentRow + dr[i];
//             int newCol = currentCol + dc[i];

//             if (isValidCell(newRow, newCol, numRows, numCols, visited) && matrix[newRow][newCol] == 1) {
//                 visited[newRow][newCol] = true;
//                 queue[rear].row = newRow;
//                 queue[rear].col = newCol;
//                 rear++;
//             }
//         }
//     }

//     printf("\n");
// }

// int main() {
//     int numRows, numCols;
//     int matrix[MAX_SIZE][MAX_SIZE];

//     printf("Enter the number of rows and columns: ");
//     scanf("%d %d", &numRows, &numCols);

//     printf("Enter the matrix (0s and 1s):\n");
//     for (int i = 0; i < numRows; i++) {
//         for (int j = 0; j < numCols; j++) {
//             scanf("%d", &matrix[i][j]);
//         }
//     }
//     int startRow, startCol;
//     printf("Enter the starting cell coordinates (row col): ");
//     scanf("%d %d", &startRow, &startCol);
//     bfs(matrix, numRows, numCols, startRow, startCol);
//     return 0;
// }
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 1001

typedef struct {
    int row;
    int col;
} Cell;

Cell queue[MAX_SIZE * MAX_SIZE];
int front, rear;
int visited[MAX_SIZE][MAX_SIZE];
int distance[MAX_SIZE][MAX_SIZE];

int dr[] = {-1, 1, 0, 0};  // Up, Down, Left, Right
int dc[] = {0, 0, -1, 1};

int n;

int isValid(int row, int col) {
    return (row >= 0 && row < n && col >= 0 && col < n);
}

void enqueue(Cell cell) {
    queue[rear++] = cell;
}

Cell dequeue() {
    return queue[front++];
}

void bfs(int startRow, int startCol, char board[MAX_SIZE][MAX_SIZE]) {
    front = rear = 0;
    
    Cell startCell = {startRow, startCol};
    enqueue(startCell);
    visited[startRow][startCol] = 1;
    distance[startRow][startCol] = 0;
    
    while (front != rear) {
        Cell current = dequeue();
        int row = current.row;
        int col = current.col;
        
        for (int i = 0; i < 4; i++) {
            int newRow = row + dr[i];
            int newCol = col + dc[i];
            
            if (isValid(newRow, newCol) && !visited[newRow][newCol] && board[newRow][newCol] != '#') {
                Cell neighbor = {newRow, newCol};
                enqueue(neighbor);
                visited[newRow][newCol] = 1;
                distance[newRow][newCol] = distance[row][col] + 1;
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    
    char board[MAX_SIZE][MAX_SIZE];
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf(" %c", &board[i][j]);
            visited[i][j] = 0;
            distance[i][j] = -1;
        }
    }
    
    int player1Row, player1Col;
    int player2Row, player2Col;
    int treasureRow1 = -1, treasureCol1 = -1;
    int treasureRow2 = -1, treasureCol2 = -1;
    
    // Find initial positions of players and the treasures
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == 'p') {
                if (player1Row == 0 && player1Col == 0) {
                    player1Row = i;
                    player1Col = j;
                } else {
                    player2Row = i;
                    player2Col = j;
                }
            } else if (board[i][j] == 't') {
                if (treasureRow1 == -1 && treasureCol1 == -1) {
                    treasureRow1 = i;
                    treasureCol1 = j;
                } else {
                    treasureRow2 = i;
                    treasureCol2 = j;
                }
            }
        }
    }
    
    // Perform BFS from player 1 position to treasure 1
    bfs(player1Row, player1Col, board);
    int player1ToTreasure1Time = distance[treasureRow1][treasureCol1];
    
    // Perform BFS from player 1 position to treasure 2
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            visited[i][j] = 0;
            distance[i][j] = -1;
        }
    }
    bfs(player1Row, player1Col, board);
    int player1ToTreasure2Time = distance[treasureRow2][treasureCol2];
    
    // Perform BFS from player 2 position to treasure 1
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            visited[i][j] = 0;
            distance[i][j] = -1;
        }
    }
    bfs(player2Row, player2Col, board);
    int player2ToTreasure1Time = distance[treasureRow1][treasureCol1];
    
    // Perform BFS from player 2 position to treasure 2
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            visited[i][j] = 0;
            distance[i][j] = -1;
        }
    }
    bfs(player2Row, player2Col, board);
    int player2ToTreasure2Time = distance[treasureRow2][treasureCol2];
    
    // Calculate the minimum time required for both players to find the treasure
    int minTime = INT_MAX;
    
    if (player1ToTreasure1Time != -1 && player2ToTreasure2Time != -1)
        minTime = player1ToTreasure1Time > player2ToTreasure2Time ? player1ToTreasure1Time : player2ToTreasure2Time;
    
    if (player1ToTreasure2Time != -1 && player2ToTreasure1Time != -1) {
        int time = player1ToTreasure2Time > player2ToTreasure1Time ? player1ToTreasure2Time : player2ToTreasure1Time;
        minTime = minTime < time ? minTime : time;
    }
    
    if (minTime == INT_MAX) {
        printf("-1\n");
    } else {
        printf("%d\n", minTime);
    }
    
    return 0;
}
