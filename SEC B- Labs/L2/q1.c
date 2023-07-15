// 1 CORRECT-
#include <stdio.h>
// The code then initializes a variable max_perimeter to zero, which will store the maximum 
// perimeter of a rectangular table that can be placed in the hall.
// The code then iterates over each cell of the hall matrix again, and for each cell (i, j)
//  that is free, it computes the minimum side length min_side of the rectangular table that can be placed with one of its sides starting at (i, j) using the dp array. Then, it iterates over all cells (k, j) below (i, j) that are also free, and for each such cell, it updates min_side to the minimum of min_side and dp[k][j], and computes the perimeter of the corresponding rectangular table as 2 * (min_side + k - i + 1). Finally, 
// it updates max_perimeter to the maximum of max_perimeter and the perimeter computed for the
//  current cell. The code prints max_perimeter-1, which is the maximum number of friends that can sit around a rectangular
//  table of maximum perimeter.

int min(int a, int b) {
    return a < b ? a : b;
}
int max(int a, int b) {
    return a > b ? a : b;
}
int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    char hall[m][n];
    for (int i = 0; i < m; i++) {
        scanf("%s", hall[i]);
    }

    int dp[m][n]; // length of the longest continuous row of free cells ending at cell (i,j)
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (hall[i][j] == 'X') {
                dp[i][j] = 0;
            } else if (i == 0 || j == 0) {
                dp[i][j] = 1;
            } else {
                dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + 1;
            }
        }
    }
    int max_perimeter = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (hall[i][j] == '.') {
                int min_side = dp[i][j];
                for (int k = i; k < m && hall[k][j] == '.'; k++) {
                    min_side = min(min_side, dp[k][j]);
                    max_perimeter = max(max_perimeter, 2 * (min_side + k - i + 1));
                }
            }
        }
    }
    printf("%d\n", max_perimeter-1);
    return 0;
}



// 3RD 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int largest_rect(int** dp, char** hall, int m, int n, int i, int j, int k, int l) {
    if (i >= k || j >= l) return 0;
    if (dp[i][j][k][l] != -1) return dp[i][j][k][l];
    int res = 0;
    if (k - i == l - j) {
        // table is a square
        int is_rect = 1;
        for (int r = i; r < k && is_rect; r++) {
            for (int c = j; c < l && is_rect; c++) {
                if (hall[r][c] == 'X') is_rect = 0;
            }
        }
        if (is_rect) res = k - i + l - j;
    } else {
        // table is a rectangle
        res = largest_rect(dp, hall, m, n, i + 1, j, k, l);
        res = max(res, largest_rect(dp, hall, m, n, i, j + 1, k, l));
        res = max(res, largest_rect(dp, hall, m, n, i, j, k - 1, l));
        res = max(res, largest_rect(dp, hall, m, n, i, j, k, l - 1));
    }
    dp[i][j][k][l] = res;
    return res;
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    char** hall = (char**)malloc(m * sizeof(char*));
    for (int i = 0; i < m; i++) {
        hall[i] = (char*)malloc((n + 1) * sizeof(char));
        scanf("%s", hall[i]);
    }
    int**** dp = (int****)malloc(m * sizeof(int***));
    for (int i = 0; i < m; i++) {
        dp[i] = (int***)malloc(n * sizeof(int**));
        for (int j = 0; j < n; j++) {
            dp[i][j] = (int**)malloc(m * sizeof(int*));
            for (int k = 0; k < m; k++) {
                dp[i][j][k] = (int*)malloc(n * sizeof(int));
                memset(dp[i][j][k], -1, n * sizeof(int));
            }
        }
    }
    int ans = largest_rect(dp, hall, m, n, 0, 0, m, n);
    printf("%d\n", ans - 1);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            free(dp[i][j]);
        }
        free(dp[i]);
        free(hall[i]);
    }
    free(dp);
    free(hall);
    return 0;
}

// 2
#include <stdio.h>
#include <stdlib.h> // include the <stdlib.h> header for fmax and fmin
#include <math.h>
void bfs(int n, int m, char arr[n][m], int* max_width, int* max_height) {
    // initialize left, right, and height arrays
    int left[m], right[m], height[m];
    for (int i = 0; i < m; i++) {
        left[i] = 0;
        right[i] = m - 1;
        height[i] = 0;
    }

    // traverse the matrix row-wise
    for (int i = 0; i < n; i++) {
        int cur_left = 0, cur_right = m - 1;
        // update height array and left array for current row
        for (int j = 0; j < m; j++) {
            if (arr[i][j] == '.') {
                height[j]++;
                left[j] = fmax(left[j], cur_left);
            } else {
                height[j] = 0;
                left[j] = 0;
                cur_left = j + 1;
            }
        }

        // update right array for current row
        for (int j = m - 1; j >= 0; j--) {
            if (arr[i][j] == '.') {
                right[j] = fmin(right[j], cur_right);
            } else {
                right[j] = m - 1;
                cur_right = j - 1;
            }
        }

        // calculate the maximum area for current row
        for (int j = 0; j < m; j++) {
            int area = (right[j] - left[j] + 1) * height[j];
            if (area > (*max_width) * (*max_height)) {
                *max_width = right[j] - left[j] + 1;
                *max_height = height[j];
            }
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    char arr[n][m];
    for (int i = 0; i < n; i++) {
        scanf("%s", arr[i]);
    }

    int max_width = 0, max_height = 0;
    bfs(n, m, arr, &max_width, &max_height);

    printf("%d\n", 2 * (max_width + max_height) - 2);
    return 0;
}
