#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}
struct MinHeap {
    int* heap;
    int capacity;
    int heap_size;
};
struct MinHeap* createMinHeap(int capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->heap = (int*)malloc(capacity * sizeof(int));
    minHeap->capacity = capacity;
    minHeap->heap_size = 0;
    return minHeap;
}
int parent(int i) {
    return (i - 1) / 2;
}
int left(int i) {
    return 2 * i + 1;
}
int right(int i) {
    return 2 * i + 2;
}
void minHeapify(struct MinHeap* minHeap, int i) {
    int smallest = i;
    int leftChild = left(i);
    int rightChild = right(i);
    if (leftChild < minHeap->heap_size && minHeap->heap[leftChild] < minHeap->heap[smallest])      
      smallest = leftChild;
    if (rightChild < minHeap->heap_size && minHeap->heap[rightChild] < minHeap->heap[smallest])  
      smallest = rightChild;
    if (smallest != i) {
        swap(&minHeap->heap[i], &minHeap->heap[smallest]);
        minHeapify(minHeap, smallest);
    }
}

int extractMin(struct MinHeap* minHeap) {
    if (minHeap->heap_size <= 0)
        return INT_MAX;
    if (minHeap->heap_size == 1) {
        minHeap->heap_size--;
        return minHeap->heap[0];
    }
    int root = minHeap->heap[0];
    minHeap->heap[0] = minHeap->heap[minHeap->heap_size - 1];
    minHeap->heap_size--;
    minHeapify(minHeap, 0);
    return root;
}
void decreaseKey(struct MinHeap* minHeap, int i, int new_val) {
    minHeap->heap[i] = new_val;
    while (i != 0 && minHeap->heap[parent(i)] > minHeap->heap[i]) {
        swap(&minHeap->heap[i], &minHeap->heap[parent(i)]);
        i = parent(i);
    }
}
void deleteKey(struct MinHeap* minHeap, int i) {
    decreaseKey(minHeap, i, INT_MIN);
    extractMin(minHeap);
}
void insertKey(struct MinHeap* minHeap, int k) {
    if (minHeap->heap_size == minHeap->capacity) {
        printf("\nOverflow: Could not insertKey\n");
        return;
    }
    int i = minHeap->heap_size;
    minHeap->heap_size++;
    minHeap->heap[i] = k;
    while (i != 0 && minHeap->heap[parent(i)] > minHeap->heap[i]) {
        swap(&minHeap->heap[i], &minHeap->heap[parent(i)]);
        i = parent(i);
    }
}
int getMin(struct MinHeap* minHeap) {
    if (minHeap->heap_size > 0)
        return minHeap->heap[0];
    else
        return INT_MAX;
}
int main() {
    struct MinHeap* minHeap = createMinHeap(11);
    insertKey(minHeap, 3);
    insertKey(minHeap, 2);
    deleteKey(minHeap, 1);
    insertKey(minHeap, 15);
    insertKey(minHeap, 5);
    insertKey(minHeap, 4);
    insertKey(minHeap, 45);
    
    printf("%d ", extractMin(minHeap));
    printf("%d ", getMin(minHeap));
    
    decreaseKey(minHeap, 2, 1);
    printf("%d", getMin(minHeap));
    
    return 0;
}
