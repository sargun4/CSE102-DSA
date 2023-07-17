// #include <stdio.h>
// #include <stdbool.h>
// #include <stdlib.h>
// #include <string.h>

// typedef struct {
//     int row;
//     int col;
// } Cell;

// bool isValid(int row, int col, int m, int n) {
//     return (row >= 0 && row < m && col >= 0 && col < n);
// }

// void bfs(char** pyramid, int m, int n, Cell start) {
//     int dx[] = {-1, 1, 0, 0}; // Up, Down, Left, Right
//     int dy[] = {0, 0, -1, 1};
    
//     int** distance = (int**)malloc(m * sizeof(int*));
//     char*** path = (char***)malloc(m * sizeof(char**));
//     for (int i = 0; i < m; i++) {
//         distance[i] = (int*)malloc(n * sizeof(int));
//         path[i] = (char**)malloc(n * sizeof(char*));
//         for (int j = 0; j < n; j++) {
//             distance[i][j] = -1;
//             path[i][j] = (char*)malloc((m + n) * sizeof(char));
//             memset(path[i][j], '\0', (m + n) * sizeof(char));
//         }
//     }
    
//     Cell* queue = (Cell*)malloc(m * n * sizeof(Cell));
//     int front = 0;
//     int rear = 0;
    
//     queue[rear++] = start;
//     distance[start.row][start.col] = 0;
    
//     while (front < rear) {
//         Cell curr = queue[front++];
        
//         // Check if current cell is a free boundary cell
//         if (curr.row == 0 || curr.row == m - 1 || curr.col == 0 || curr.col == n - 1) {
//             printf("YES\n");
//             printf("%d\n", distance[curr.row][curr.col]);
//             printf("%s\n", path[curr.row][curr.col]);
            
//             // Free memory
//             for (int i = 0; i < m; i++) {
//                 free(distance[i]);
//                 for (int j = 0; j < n; j++) {
//                     free(path[i][j]);
//                 }
//                 free(path[i]);
//             }
//             free(distance);
//             free(path);
//             free(queue);
            
//             return;
//         }
        
//         for (int i = 0; i < 4; i++) {
//             int newRow = curr.row + dx[i];
//             int newCol = curr.col + dy[i];
            
//             if (isValid(newRow, newCol, m, n) && (pyramid[newRow][newCol] == '.' || pyramid[newRow][newCol] == 'A' || pyramid[newRow][newCol] == 'M') && distance[newRow][newCol] == -1) {
//                 queue[rear].row = newRow;
//                 queue[rear].col = newCol;
//                 distance[newRow][newCol] = distance[curr.row][curr.col] + 1;
//                 strcpy(path[newRow][newCol], path[curr.row][curr.col]);
//                 switch (i) {
//                     case 0:
//                         strcat(path[newRow][newCol], "U");
//                         break;
//                     case 1:
//                         strcat(path[newRow][newCol], "D");
//                         break;
//                     case 2:
//                         strcat(path[newRow][newCol], "L");
//                         break;
//                     case 3:
//                         strcat(path[newRow][newCol], "R");
//                         break;
//                 }
                
//                 rear++;
//             }
//         }
//     }
    
//     printf("NO\n");
    
//     // Free memory
//     for (int i = 0; i < m; i++) {
//         free(distance[i]);
//         for (int j = 0; j < n; j++) {
//             free(path[i][j]);
//         }
//         free(path[i]);
//     }
//     free(distance);
//     free(path);
//     free(queue);
// }

// int main() {
//     int m, n;
//     scanf("%d %d", &m, &n);
    
//     char** pyramid = (char**)malloc(m * sizeof(char*));
    
//     for (int i = 0; i < m; i++) {
//         pyramid[i] = (char*)malloc((n + 1) * sizeof(char));
//         scanf("%s", pyramid[i]);
//     }
    
//     Cell start;
    
//     // Find Kone's initial location
//     for (int i = 0; i < m; i++) {
//         for (int j = 0; j < n; j++) {
//             if (pyramid[i][j] == 'A') {
//                 start.row = i;
//                 start.col = j;
//                 break;
//             }
//         }
//     }
    
//     bfs(pyramid, m, n, start);
    
//     // Free memory
//     for (int i = 0; i < m; i++) {
//         free(pyramid[i]);
//     }
//     free(pyramid);
    
//     return 0;
// }

// // Read the values of m and n.
// // Read the pyramid layout and store it in a 2D matrix.
// // Find Kone's initial location (marked as 'A') and store its coordinates.
// // Create a 2D matrix to store the distance traveled to reach each cell, initialized with -1.
// // Create a 2D matrix to store the path taken to reach each cell, initialized with empty strings.
// // Create a queue to perform BFS.
// // Enqueue Kone's initial location into the queue.
// // Set the distance of Kone's initial location to 0 and the path to an empty string.
// // While the queue is not empty:
// // a. Dequeue a cell from the front of the queue.
// // b. Check if the cell is a free boundary cell (on any edge of the pyramid). If yes, print "YES", the distance traveled, and the path taken, then return.
// // c. Check all four adjacent cells (up, down, left, right):
// // - If the adjacent cell is within the bounds of the pyramid and is a free cell ('.'), a mummy ('M'), or Kone's initial location ('A'), and the distance of the adjacent cell is -1 (not visited):
// // - Set the distance of the adjacent cell to the current distance + 1.
// // - Set the path of the adjacent cell to the current path + the direction of the move (U, D, L, R).
// // - Enqueue the adjacent cell into the queue.
// // If no free boundary cell is found, print "NO".
