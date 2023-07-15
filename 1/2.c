#include <stdio.h>

#define ROWS 4
#define COLS 4

void spiralPrint(int m, int n, int a[ROWS][COLS])
{
    int i, k = 0, l = 0;

    while (k < m && l < n) {
        for (i = l; i < n; ++i) {
            printf("%d ", a[k][i]);
        }
        k++;

        for (i = k; i < m; ++i) {
            printf("%d ", a[i][n - 1]);
        }
        n--;

        if (k < m) {
            for (i = n - 1; i >= l; --i) {
                printf("%d ", a[m - 1][i]);
            }
            m--;
        }

        if (l < n) {
            for (i = m - 1; i >= k; --i) {
                printf("%d ", a[i][l]);
            }
            l++;
        }
    }
}

int main()
{
    int a[ROWS][COLS] = {{1, 2, 3, 4},
                         {5, 6, 7, 8},
                         {9, 10, 11, 12},
                         {13, 14, 15, 16}};

    spiralPrint(ROWS, COLS, a);
    return 0;
}
