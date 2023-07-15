#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define N 8
// Define the moves of the knight
int x_moves[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
int y_moves[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };
// Check if a move is valid
bool is_valid_move(int x, int y, int board[N][N]) {
    return (x >= 0 && x < N && y >= 0 && y < N && board[x][y] == -1);
}

// Print the solution
void print_solution(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%2d ", board[i][j]);
        }
        printf("\n");
    }
    return;
}

// Recursive function to solve the Knight's Tour problem
bool solve_knight_tour(int x, int y, int move_number, int board[N][N]) {
    // Base case: all squares have been visited
    if (move_number == N*N) {
        return true;
    }
    // Try all possible moves from the current square
    for (int i = 0; i < 8; i++) {
        int next_x = x + x_moves[i];
        int next_y = y + y_moves[i];
        if (is_valid_move(next_x, next_y, board)) {
            // Mark the square as visited
            board[next_x][next_y] = move_number;
            // Recursive call to explore further
            if (solve_knight_tour(next_x, next_y, move_number+1, board)) {
                return true;
            }
            // Backtrack: undo the move and try a different move
            board[next_x][next_y] = -1;
        }
    }
    // If no moves were successful, return false
    return false;
}

int main() {
    int board[N][N];
    // Initialize the board with -1 (unvisited)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = -1;
        }
    }
    // Start the tour from the top-left corner
    int start_x = 0;
    int start_y = 0;
    board[start_x][start_y] = 0;
    // Try to solve the Knight's Tour problem starting from each square
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (solve_knight_tour(i, j, 1, board)) {
                printf("Solution starting from (%d, %d):\n", i, j);
                print_solution(board);
                // Reset the board for the next solution
                for (int k = 0; k < N; k++) {
                    for (int l = 0; l < N; l++) {
                        board[k][l] = -1;
                    }
                }
                // Mark the starting square as visited
                board[i][j] = 0;
            }
        }
    }
    return 0;
}
