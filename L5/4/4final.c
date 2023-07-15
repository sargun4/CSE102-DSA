#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1000
#define INFINITY 1e9


int land[MAX_SIZE][MAX_SIZE];
int fire_reachin_time[MAX_SIZE][MAX_SIZE];
int visited[MAX_SIZE][MAX_SIZE];


int m, n;

struct matrix{
    int row;
    int col;
};
int validcell(int row, int col) {
    return row >= 0 && row < m && col >= 0 && col < n;
}

void BFS() {
    struct matrix* queue = (struct matrix*)malloc(m * n * sizeof(struct matrix));
    int front = 0;
    int rear = 0;
    
    
    for (int i = 0; i < m; i++) {
        if (land[i][0] == 0) {
            queue[rear].row = i;
            queue[rear].col = 0;
            fire_reachin_time[i][0] = 1;
            visited[i][0] = 1;
            rear++;
        }
        if (land[i][n - 1] == 0) {
            queue[rear].row = i;
            queue[rear].col = n - 1;
            fire_reachin_time[i][n - 1] = 1;
            visited[i][n - 1] = 1;
            rear++;
        }
    }
    for (int j = 1; j < n - 1; j++) {
        if (land[0][j] == 0) {
            queue[rear].row = 0;
            queue[rear].col = j;
            fire_reachin_time[0][j] = 1;
            visited[0][j] = 1;
            rear++;
        }
        if (land[m - 1][j] == 0) {
            queue[rear].row = m - 1;
            queue[rear].col = j;
            fire_reachin_time[m - 1][j] =1;
            visited[m - 1][j] = 1;
            rear++;
        }
    }

    int row_dirn[] = {-1, 1, 0, 0};
    int col_dirn[] = {0, 0, -1, 1};

    //  BFS
    while (front < rear) {
        struct matrix current = queue[front];
        front++;
        for (int i = 0; i < 4; i++) {
            int newRow = current.row + row_dirn[i];
            int newCol = current.col + col_dirn[i];
            if (validcell(newRow, newCol) && !visited[newRow][newCol] && land[newRow][newCol] == 0) {
                fire_reachin_time[newRow][newCol] = fire_reachin_time[current.row][current.col] + 1;
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
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &land[i][j]);
            fire_reachin_time[i][j] = INFINITY;
            visited[i][j] = 0;
        }
    }
    BFS();

    int q;
    scanf("%d", &q);

    while (q--) {
        int x, y;
        scanf("%d %d", &x, &y);

        if (fire_reachin_time[x][y] == INFINITY) {
            printf("infinity\n");
        } else {
            printf("%d\n", fire_reachin_time[x][y]);
        }
    }

    return 0;
}
