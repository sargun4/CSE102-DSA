#include <stdio.h>

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int rows, cols;
    scanf("%d %d", &rows, &cols);

    char hall[rows][cols];
    for (int i = 0; i < rows; i++) {
        scanf("%s", hall[i]);
    }

    int mat[rows][cols]; // length of the longest continuous row of free cells ending at cell (i,j)
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (hall[i][j] == 'X') {
                mat[i][j] = 0;
            } else if (i == 0 || j == 0) {
                mat[i][j] = 1;
            } else {
                mat[i][j] = min(mat[i-1][j], mat[i][j-1]) + 1;
            }
        }
    }

    int max_perimeter = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (hall[i][j] == '.') {
                int min_side = mat[i][j];
                for (int k = i; k < rows && hall[k][j] == '.'; k++) {
                    min_side = min(min_side, mat[k][j]);
                    max_perimeter = max(max_perimeter, 2 * (min_side + k - i + 1));
                }
            }
        }
    }

    printf("%d\n", max_perimeter-1);
    return 0;
}
