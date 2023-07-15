#include <stdio.h>
#include <stdlib.h>
void maxheapify(int arr[], int size, int idx) {
    int largest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    if (left < size && arr[left] > arr[largest])
        largest = left;
    if (right < size && arr[right] > arr[largest])
        largest = right;
    if (largest != idx) {
        int temp = arr[idx];
        arr[idx] = arr[largest];
        arr[largest] = temp;
        maxheapify(arr, size, largest);
    }
}
void buildmxheap(int arr[], int size) {
    for (int i = size / 2 - 1; i >= 0; i--) {
        maxheapify(arr, size, i);
    }
}
int extractmax(int arr[], int* size) {
    if (*size == 0)
        return 0;
    int maxitem = arr[0];
    arr[0]--;
    if (arr[0] != 0) {
        maxheapify(arr, *size, 0);
    } else {
        arr[0] = arr[*size - 1];
        (*size)--;
        maxheapify(arr, *size, 0);
    }
    return maxitem;
}
int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int* items = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &items[i]);
    }
    long long maxamt = 0;
    buildmxheap(items, n);

    while (n > 0 && k > 0) {
        int solditmes = extractmax(items, &n);
        maxamt += solditmes;
        k--;
    }

    printf("%lld\n", maxamt);
    free(items);
    return 0;
}