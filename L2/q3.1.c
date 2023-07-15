#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 1000000
#define MAX_QUEUE_SIZE 1000000

typedef struct {
    int *array;
    int head, tail;
} Queue;

typedef struct {
    Queue *array;
    int size, top;
} Stack;

int max(int a, int b) {
    return (a > b) ? a : b;
}

void enqueue(Queue *queue, int value) {
    queue->array[queue->tail] = value;
    queue->tail++;
}

int dequeue(Queue *queue) {
    if (queue->head == queue->tail) {
        return -1;
    }
    int value = queue->array[queue->head];
    queue->head++;
    return value;
}

void push(Stack *stack, Queue queue) {
    stack->array[stack->top] = queue;
    stack->top++;
}

Queue pop(Stack *stack) {
    stack->top--;
    return stack->array[stack->top];
}

int max_sum_pairs(Queue *queue, int k) {
    int count = 0;
    int sum = 0;
    int max_count = 0;
    int i = queue->head;
    int j = queue->head;
    while (j < queue->tail) {
        if (sum + queue->array[j] < k) {
            sum += queue->array[j];
            j++;
        } else {
            if (sum + queue->array[j] - queue->array[i] >= k) {
                count++;
                sum += queue->array[j] - queue->array[i];
                i++;
            } else {
                sum -= queue->array[i];
                i++;
            }
        }
        max_count = max(max_count, count);
    }
    return max_count;
}

int main() {
    int q;
    scanf("%d", &q);

    Stack stack;
    stack.array = (Queue*) malloc(MAX_STACK_SIZE * sizeof(Queue));
    stack.size = MAX_STACK_SIZE;
    stack.top = 0;

    for (int i = 0; i < q; i++) {
        char operation[15];
        scanf("%s", operation);
        if (strcmp(operation, "Push") == 0) {
            int k;
            scanf("%d", &k);
            Queue queue;
            queue.array = (int*) malloc(MAX_QUEUE_SIZE * sizeof(int));
            queue.head = 0;
            queue.tail = 1;
            queue.array[0] = k;
            push(&stack, queue);
        } else if (strcmp(operation, "Enqueue") == 0) {
            int k;
            scanf("%d", &k);
            if (stack.top == 0) {
                Queue queue;
                queue.array = (int*) malloc(MAX_QUEUE_SIZE * sizeof(int));
                queue.head = 0;
                queue.tail = 1;
                queue.array[0] = k;
                push(&stack, queue);
            } else {
                enqueue(&(stack.array[stack.top-1]), k);
            }
        } else if (strcmp(operation, "Pop") == 0) {
            if (stack.top == 0) {
                printf("-1\n");
            } else {
                dequeue(&(stack.array[stack.top-1]));
                if (stack.array[stack.top-1].head == stack.array[stack.top-1].tail) {
                    pop(&stack);
                }
            }
        } else if (strcmp(operation, "Dequeue") == 0) {
            if (stack.top == 0) {
    printf("-1\n");
    } else {
    Queue* top_queue = stack.arr[stack.top-1];
    if (top_queue->size == 0) {
    free(stack.arr[stack.top-1]);
    stack.top--;
    if (stack.top == 0) {
    printf("-1\n");
    } else {
    top_queue = stack.arr[stack.top-1];
    printf("%d\n", top_queue->arr[top_queue->front]);
    top_queue->front = (top_queue->front + 1) % MAX_SIZE;
    top_queue->size--;
    }
    } else {
    printf("%d\n", top_queue->arr[top_queue->front]);
    top_queue->front = (top_queue->front + 1) % MAX_SIZE;
    top_queue->size--;
    }
    }
    } else if (strcmp(operation, "MaxSumPairs") == 0) {
    int k;
    scanf("%d", &k);
    Queue* top_queue = stack.arr[stack.top-1];
    int max_pairs = 0;
    int curr_sum = 0;
    for (int i = top_queue->front; i != top_queue->front + top_queue->size; i++) {
    int j = i % MAX_SIZE;
    if (j == top_queue->front && curr_sum < k) {
    continue;
    } else if (j == top_queue->front) {
    curr_sum -= top_queue->arr[j];
    }
    if (curr_sum + top_queue->arr[j] >= k) {
    max_pairs += top_queue->size - (j - top_queue->front + 1);
    curr_sum = 0;
    } else {
    curr_sum += top_queue->arr[j];
    }
    }
    printf("%d\n", max_pairs);
    free(stack.arr[stack.top-1]);
    stack.top--;
    }
    }
    return 0;
}



