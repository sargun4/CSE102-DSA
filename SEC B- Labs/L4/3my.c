#include <stdio.h>
#include <stdlib.h>
void merge(long long arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    long long L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void mergesort(long long arr[], int l, int r) {
    if (l < r) {
        int mid = l + (r - l) / 2;

        mergesort(arr, l, mid);
        mergesort(arr, mid + 1, r);

        merge(arr, l, mid, r);
    }
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    long long hostility[n];
    long long humor[n];
    for (int i = 0; i < n; i++) {
        scanf("%lld", &hostility[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%lld", &humor[i]);
    }
    mergesort(hostility, 0, n - 1);
    mergesort(humor, 0, n - 1);
    int maxsumidx = n*n;
    long long sum[maxsumidx];
    int count = 0;

    for (int i = n - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {
            sum[count++] = hostility[i] + humor[j];
        }
    }
    mergesort(sum, 0, count - 1);

    for (int i = 0; i < q; i++) {
        int query;
        scanf("%d", &query);
        printf("%lld\n", sum[query - 1]);
    }
    return 0;
}
