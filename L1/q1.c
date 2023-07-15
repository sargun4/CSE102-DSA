#include <stdio.h>

void merge(int arr[], int l, int mid, int r) {
    int i, j, k;
    int n1 = mid - l + 1;
    int n2 = r - mid;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    } while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergesort(int arr[], int l, int r) {
    if (l < r) {
        int mid = l + (r - l) / 2;
        mergesort(arr, l, mid);
        mergesort(arr, mid + 1, r);
        merge(arr, l, mid, r);
    }
}

int main() {
    int n, i;
    scanf("%d", &n);

    int arr[n], sorted_arr[n], pos[n];
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        sorted_arr[i] = arr[i];
    }

    // Sort the array using merge sort
    mergesort(sorted_arr, 0, n - 1);

    // Create a hash table to store the positions of each element
    for (i = 0; i < n; i++) {
        pos[arr[i] - 1] = i;
    }

    // Iterate over the sorted array and calculate the number of swaps required
    int swaps = 0;
    for (i = 0; i < n; i++) {
        int curr_pos = pos[sorted_arr[i] - 1];
        if (i != curr_pos) {
            pos[arr[i] - 1] = curr_pos;
            pos[sorted_arr[i] - 1] = i;
            int temp = arr[i];
            arr[i] = arr[curr_pos];
            arr[curr_pos] = temp;
            swaps++;
        }
    }
    printf("%d\n", swaps);
    return 0;
}
