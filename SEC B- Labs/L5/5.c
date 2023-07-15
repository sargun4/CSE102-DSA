// #include <stdio.h>
// #include <stdlib.h>

// #define MAX_SIZE 1001

// typedef struct {
//     int row;
//     int col;
// } Cell;

// Cell queue[MAX_SIZE * MAX_SIZE];
// int front, rear;
// int visited[MAX_SIZE][MAX_SIZE];
// int distance[MAX_SIZE][MAX_SIZE];

// int dr[] = {-1, 1, 0, 0};  // Up, Down, Left, Right
// int dc[] = {0, 0, -1, 1};

// int n;

// int isValid(int row, int col) {
//     return (row >= 0 && row < n && col >= 0 && col < n);
// }

// void enqueue(Cell cell) {
//     queue[rear++] = cell;
// }

// Cell dequeue() {
//     return queue[front++];
// }

// void bfs(int startRow, int startCol, char board[MAX_SIZE][MAX_SIZE]) {
//     front = rear = 0;
    
//     Cell startCell = {startRow, startCol};
//     enqueue(startCell);
//     visited[startRow][startCol] = 1;
//     distance[startRow][startCol] = 0;
    
//     while (front != rear) {
//         Cell current = dequeue();
//         int row = current.row;
//         int col = current.col;
        
//         for (int i = 0; i < 4; i++) {
//             int newRow = row + dr[i];
//             int newCol = col + dc[i];
            
//             if (isValid(newRow, newCol) && !visited[newRow][newCol] && board[newRow][newCol] != '#') {
//                 Cell neighbor = {newRow, newCol};
//                 enqueue(neighbor);
//                 visited[newRow][newCol] = 1;
//                 distance[newRow][newCol] = distance[row][col] + 1;
//             }
//         }
//     }
// }

// int main() {
//     scanf("%d", &n);
    
//     char board[MAX_SIZE][MAX_SIZE];
    
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++) {
//             scanf(" %c", &board[i][j]);
//             visited[i][j] = 0;
//             distance[i][j] = -1;
//         }
//     }
    
//     int player1Row, player1Col;
//     int player2Row, player2Col;
//     int treasureRow, treasureCol;
    
//     // Find initial positions of players and the treasure
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++) {
//             if (board[i][j] == 'p') {
//                 if (player1Row == 0 && player1Col == 0) {
//                     player1Row = i;
//                     player1Col = j;
//                 } else {
//                     player2Row = i;
//                     player2Col = j;
//                 }
//             } else if (board[i][j] == 't') {
//                 treasureRow = i;
//                 treasureCol = j;
//             }
//         }
//     }
    
//     // Perform BFS from player 1 and player 2 positions
//     bfs(player1Row, player1Col, board);
//     int player1Time = distance[treasureRow][treasureCol];
    
//     for (int i = 0; i < MAX_SIZE; i++) {
//         for (int j = 0; j < MAX_SIZE; j++) {
//             visited[i][j] = 0;
//             distance[i][j] = -1;
//         }
//     }
    
//     bfs(player2Row, player2Col, board);
//     int player2Time = distance[treasureRow][treasureCol];
    
//     // Calculate the minimum time required for both players to find the treasure
//     if (player1Time == -1 || player2Time == -1) {
//         printf("-1\n");
//     } else {
//         int minTime = (player1Time > player2Time) ? player1Time : player2Time;
//         printf("%d\n", minTime);
//     }
    
//     return 0;
// }
#include <stdio.h>
#include <stdlib.h>

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
    
    int player1Row = -1, player1Col = -1;
    int player2Row = -1, player2Col = -1;
    int treasureRow = -1, treasureCol = -1;
    
    // Find initial positions of players and the treasure
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == 'p') {
                if (player1Row == -1 && player1Col == -1) {
                    player1Row = i;
                    player1Col = j;
                } else {
                    player2Row = i;
                    player2Col = j;
                }
            } else if (board[i][j] == 't') {
                treasureRow = i;
                treasureCol = j;
            }
        }
    }
    
    // Perform BFS from player 1 and player 2 positions
    bfs(player1Row, player1Col, board);
    int player1Time = distance[treasureRow][treasureCol];
    
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            visited[i][j] = 0;
            distance[i][j] = -1;
        }
    }
    
    bfs(player2Row, player2Col, board);
    int player2Time = distance[treasureRow][treasureCol];
    
    // Calculate the minimum time required for both players to find the treasure
    if (player1Time == -1 || player2Time == -1) {
        printf("-1\n");
    } else {
        int minTime = (player1Time > player2Time) ? player1Time : player2Time;
        printf("%d\n", minTime);
    }
    
    return 0;
}
