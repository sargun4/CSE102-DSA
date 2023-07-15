#include <stdio.h>
#define N 8

// INCORRECT
int board[N][N];
int posx[] = {2, 1, -1, -2, -2, -1, 1, 2};
int posy[] = {1, 2, 2, 1, -1, -2, -2, -1};
int is_valid(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N && board[x][y] == -1);
}
int get_degree(int x, int y) {
    int degree = 0;
    for (int i = 0; i < 8; i++) {
        int newx = x + posx[i];
        int newy = y + posy[i];
        if (is_valid(newx, newy)) {
            degree++;
        }
    }
    return degree;
}
int get_min_degree(int x, int y) {
    int min_deg = N + 1, min_x = -1, min_y = -1;
    for (int i = 0; i < 8; i++) {
        int newx = x + posx[i];
        int newy = y + posy[i];
        if (is_valid(newx, newy)) {
            int deg = get_degree(newx, newy);
            if (deg < min_deg) {
                min_deg = deg;
                min_x = newx;
                min_y = newy;
            }
        }
    }
    return (min_x == -1 && min_y == -1) ? -1 : (min_x * N + min_y);
}
int solve_knights_tour(int x, int y, int move) {
    if (move == N * N) {
        return 1;
    }
    int next_move;
    for (int i = 0; i < 8; i++) {
        int newx = x + posx[i];
        int newy = y + posy[i];
        if (is_valid(newx, newy)) {
            board[newx][newy] = move;
            next_move = get_min_degree(newx, newy);
            if (next_move == -1 || solve_knights_tour(newx, newy, move + 1)) {
                return 1;
            }
            board[newx][newy] = -1;
        }
    }
    return 0;
}
int main() {
    // Initialize the board
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = -1;
        }
    }
    // Starting position
    int startx = 0, starty = 0;
    board[startx][starty] = 0;

    if (solve_knights_tour(startx, starty, 1)) {
        printf("Solution exists:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%2d ", board[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("Solution does not exist.\n");
    }
    return 0;
}
