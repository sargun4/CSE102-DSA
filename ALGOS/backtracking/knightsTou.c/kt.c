#include <stdio.h>

int grid[8][8] = {0};

struct Tuple {
    int x;
    int y;
};

struct Tuple possibilites[8];

int getpossibilities(int x, int y) {
    int posx[] = {2, 1, 2, 1, -2, -1, -2, -1};
    int posy[] = {1, 2, -1, -2, 1, 2, -1, -2};
    int count = 0;
    for (int i = 0; i < 8; i++) {
        if (x + posx[i] >= 0 && x + posx[i] < 8 && y + posy[i] >= 0 && y + posy[i] < 8 && grid[x + posx[i]][y + posy[i]] == 0) {
            possibilites[count].x = x + posx[i];
            possibilites[count].y = y + posy[i];
            count++;
        }
    }
    return count;
}

void solve() {
    int ctr = 2;
    int x = 0, y = 0;
    for (int i = 0; i < 8 * 8 - 1; i++) {
        int num_moves = getpossibilities(x, y);
        struct Tuple pos[num_moves];
        for (int j = 0; j < num_moves; j++) {
            pos[j] = possibilites[j];
        }
        struct Tuple min = pos[0];
        for (int j = 1; j < num_moves; j++) {
            if (getpossibilities(pos[j].x, pos[j].y) < getpossibilities(min.x, min.y)) {
                min = pos[j];
            }
        }
        x = min.x;
        y = min.y;
        grid[x][y] = ctr;
        ctr++;
    }
}

void print(void) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            printf("%2d ", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

int main() {
    grid[0][0] = 1;
    print();
    solve();
    print();
    return 0;
}
