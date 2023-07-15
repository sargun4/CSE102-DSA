// You are given a sorted array of 32-bit integers and q queries. For each query, you need to find the index (zero-based) of the first occurrence of element x in the array. If x is not present in the array, you should print the smallest index at which x can be inserted so that the array remains sorted.
// Input
// The first line of the input contains integers n and q
//  (0<n,q≤105)
// , the length of the array and the number of queries. The second line contains n elements of the array, sorted in non-decreasing order. The third line contains q queries.
// Output
// For each query, output a single integer on a new line - the index (zero-based) of the first occurrence of x in the array, or the smallest index at which x can be inserted so that the array remains sorted.

// input
// 6 6
// 1 2 2 3 4 5
// 1 2 4 5 10 0
// output
// 0
// 1
// 4
// 5
// 6
// 0
// input
// 5 4
// 10 20 25 30 35
// 1 11 31 25
// output
// 0
// 1
// 4
// 2

#include <stdio.h>
int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    for (int i = 0; i < q; i++) {
        int x;
        scanf("%d", &x);

        int left = 0, right = n - 1, ans = n;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (arr[mid] >= x) {
                ans = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        if (arr[ans] == x) {
            printf("%d\n", ans);
        } else {
            printf("%d\n", ans);
        }
    }
    return 0;
}

