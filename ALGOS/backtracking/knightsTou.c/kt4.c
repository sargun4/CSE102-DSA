#include <stdio.h>
#include <stdbool.h>

#define N 8

int board[N][N] = {0};
int moves[8][2] = {{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};

bool is_valid(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N && board[x][y] == 0);
}

bool knights_tour(int x, int y, int move_number) {
    if (move_number == N*N) {
        return true;
    }
    for (int i = 0; i < 8; i++) {
        int next_x = x + moves[i][0];
        int next_y = y + moves[i][1];
        if (is_valid(next_x, next_y)) {
            board[next_x][next_y] = move_number;
            if (knights_tour(next_x, next_y, move_number + 1)) {
                return true;
            }
            board[next_x][next_y] = 0;
        }
    }
    return false;
}

void print_board() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%2d ", board[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int startx = 0;
    int starty = 0;
    board[startx][starty] = 1;
    if (knights_tour(startx, starty, 2)) {
        printf("Found solution:\n");
        print_board();
    } else {
        printf("No solution found.\n");
    }
    return 0;
}
