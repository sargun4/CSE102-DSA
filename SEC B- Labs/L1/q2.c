// #include <stdio.h>

// #define MAX_M 10000
// #define MAX_N 10000

// int m, n;
// int A[MAX_M][MAX_N];

// int col_sum[MAX_N];
// int col_indices[MAX_N];

// void swap(int *a, int *b) {
//     int tmp = *a;
//     *a = *b;
//     *b = tmp;
// }

// void quicksort(int arr[], int lo, int hi){
//     if (lo >= hi) {
//         return;
//     }
//     int p = partition(arr, lo, hi);
//     quicksort(arr, lo, p - 1);
//     quicksort(arr, p + 1, hi);
// }

// int partition(int arr[], int lo, int hi){
//     int pivot = arr[lo];
//     int left = lo;
//     int right = hi;
//     while (left < right) {
//         while (left <= right && arr[left] <= pivot) {
//             left += 1;
//         }
//         while (right >= left && arr[right] > pivot) {
//             right -= 1;
//         }
//         if (left < right) {
//             swap(arr, left, right);
//         }
//     }
//     swap(arr, lo, right);
//     return right;
// }


// int cmp_cols(const void *a, const void *b) {
//     int col_a = *(int *)a;
//     int col_b = *(int *)b;
//     if (col_sum[col_a] != col_sum[col_b]) {
//         return col_sum[col_a] - col_sum[col_b];
//     } else {
//         return col_a - col_b;
//     }
// }

// int main() {
//     scanf("%d%d", &m, &n);
//     for (int i = 0; i < m; i++) {
//         for (int j = 0; j < n; j++) {
//             scanf("%d", &A[i][j]);
//             col_sum[j] += A[i][j];
//             col_indices[j] = j;
//         }
//     }
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n - i - 1; j++) {
//             if (col_sum[col_indices[j]] > col_sum[col_indices[j+1]]) {
//                 swap(&col_indices[j], &col_indices[j+1]);
//             }
//         }
//     }
//     for (int i = 0; i < m; i++) {
//         for (int j = 0; j < n; j++) {
//             printf("%d%c", A[i][col_indices[j]], j == n - 1 ? '\n' : ' ');
//         }
//     }
//     return 0;
// }
#include <stdio.h>

#define MAX_M 10000
#define MAX_N 10000

int m, n;
int A[MAX_M][MAX_N];

int col_sum[MAX_N];
int col_indices[MAX_N];

void swap(int a, int b) {
    int tmp = a;
    a = b;
    b = tmp;
}
int partition(int arr[], int lo, int hi){
    int pivot = arr[lo];
    int left = lo;
    int right = hi;
    while (left < right) {
        while (left <= right && arr[left] <= pivot) {
            left += 1;
        }
        while (right >= left && arr[right] > pivot) {
            right -= 1;
        }
        if (left < right) {
            swap(left, right);
        }
    }
    swap(lo, right);
    return right;
}
void quicksort(int arr[], int lo, int hi){
    if (lo >= hi) {
        return;
    }
    int p = partition(arr, lo, hi);
    quicksort(arr, lo, p - 1);
    quicksort(arr, p + 1, hi);
}

int cmp_cols(const void *a, const void *b) {
    int col_a = *(int *)a;
    int col_b = *(int *)b;
    if (col_sum[col_a] != col_sum[col_b]) {
        return col_sum[col_a] - col_sum[col_b];
    } else {
        return col_a - col_b;
    }
}

int main() {
    scanf("%d %d\n", &m, &n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &A[i][j]);
            col_sum[j] += A[i][j];
            col_indices[j] = j;
        }
    }
    for (int i = 0; i < n; i++) {
        
        for (int j = 0; j < n - i - 1; j++) {
            if (col_sum[col_indices[j]] > col_sum[col_indices[j+1]]) {
                swap(col_indices[j], col_indices[j+1]);
            }
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d%c", A[i][col_indices[j]], j == n - 1 ? '\n' : ' ');
        }
    }
    return 0;
}

// #include <stdio.h>

// #define MAX_M 10000
// #define MAX_N 10000

// int m, n;
// int A[MAX_M][MAX_N];

// int col_sum[MAX_N];
// int col_indices[MAX_N];

// int cmp_cols(const void *a, const void *b) {
//     int col_a = *(int *)a;
//     int col_b = *(int *)b;
//     if (col_sum[col_a] != col_sum[col_b]) {
//         return col_sum[col_a] - col_sum[col_b];
//     } else {
//         return col_a - col_b;
//     }
// }

// int main() {
//     scanf("%d%d", &m, &n);
//     for (int i = 0; i < m; i++) {
//         for (int j = 0; j < n; j++) {
//             scanf("%d", &A[i][j]);
//             col_sum[j] += A[i][j];
//             col_indices[j] = j;
//         }
//     }
//     qsort(col_indices, n, sizeof(int), cmp_cols);
//     for (int i = 0; i < m; i++) {
//         for (int j = 0; j < n; j++) {
//             printf("%d%c", A[i][col_indices[j]], j == n - 1 ? '\n' : ' ');
//         }
//     }
//     return 0;
// }
