#include <stdio.h>
#include <stdlib.h>
#define MAX_N 10000
#define MAX_TU 1000000
#define MAX_TI 100000
typedef struct {
    int size;
    int *data;
} HEAP;
void goats_heap(HEAP *heap, int max_size) {
    heap->size = 0;
    heap->data = (int*) malloc(max_size * sizeof(int));
}
void heap_insert(HEAP *heap, int value) {
    int i = heap->size++;
    while (i > 0) {
        int j = (i - 1) / 2;
        if (heap->data[j] <= value) break;
        heap->data[i] = heap->data[j];
        i = j;
    }
    heap->data[i] = value;
}
int remove_min(HEAP *heap) {
    int minval = heap->data[0];
    int lastval = heap->data[--heap->size];
    int i = 0;
    while (2 * i + 1 < heap->size) {
        int j = 2 * i + 1;
        if (j + 1 < heap->size && heap->data[j + 1] < heap->data[j]) j++;
        if (heap->data[j] >= lastval) break;
        heap->data[i] = heap->data[j];
        i = j;
    }
    heap->data[i] = lastval;
    return minval;
}
int heap_min(const HEAP *heap) {
    return heap->data[0];
}
int main() {
    int N, Tu, Ti[MAX_N];
    scanf("%d %d", &N, &Tu);
    for (int i = 0; i < N; i++) {
        scanf("%d", &Ti[i]);
    }
    int lo = 1, hi = N;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        HEAP heap;
        goats_heap(&heap, mid);
        for (int i = 0; i < mid; i++) {
            heap_insert(&heap, Ti[i]);
        }
        int max_time = 0;
        for (int i = mid; i < N; i++) {
            int next_time = heap_min(&heap) + Ti[i];
            heap_insert(&heap, next_time);
            if (next_time > max_time) {
                max_time = next_time;
            }
        }
        int total_time = max_time;
        if (total_time <= Tu) {
            hi = mid - 1;  
        } else {
            lo = mid + 1;  }
    }
    printf("%d\n", lo);  
    return 0;
}
