#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_Q 1000000

typedef struct {
    int *arr;
    int front, rear, size;
} Queue;

void initQueue(Queue *q, int size) {
    q->arr = (int *)malloc(size * sizeof(int));
    q->front = q->rear = -1;
    q->size = size;
}

int isQueueEmpty(Queue *q) {
    return q->front == -1;
}

int isQueueFull(Queue *q) {
    return (q->rear + 1) % q->size == q->front;
}

void enqueue(Queue *q, int val) {
    if (isQueueFull(q)) {
        return;
    } else if (isQueueEmpty(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % q->size;
    }
    q->arr[q->rear] = val;
}

int dequeue(Queue *q) {
    if (isQueueEmpty(q)) {
        return -1;
    } else if (q->front == q->rear) {
        int val = q->arr[q->front];
        q->front = q->rear = -1;
        return val;
    } else {
        int val = q->arr[q->front];
        q->front = (q->front + 1) % q->size;
        return val;
    }
}

void deleteQueue(Queue *q) {
    free(q->arr);
    q->arr = NULL;
    q->front = q->rear = q->size = 0;
}
typedef struct Stack {
    void **arr;
    int capacity;
    int top;
    int rear;
    int front;
} Stack ;

Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->arr = (void**)malloc(capacity * sizeof(void*));
    stack->capacity = capacity;
    stack->front = -1;
    stack->rear = -1;
    return stack;
}

int main() {
    int Q;
    scanf("%d", &Q);
    Stack* stack = createStack(Q);
    
    while (Q--) {
        char op[15];
        scanf("%s", op);
        
        if (strcmp(op, "Push") == 0) {
            int K;
            scanf("%d", &K);
            Queue* newQueue = createQueue(1);
            enqueue(newQueue, K);
            push(stack, newQueue);
        }
        else if (strcmp(op, "Enqueue") == 0) {
            int K;
            scanf("%d", &K);
            if (isStackEmpty(stack)) {
                Queue* newQueue = createQueue(1);
                enqueue(newQueue, K);
                push(stack, newQueue);
            }
            else {
                Queue* topQueue = (Queue*)stack->arr[stack->rear];
                enqueue(topQueue, K);
            }
        }
        else if (strcmp(op, "Pop") == 0) {
            if (isStackEmpty(stack)) {
                printf("-1\n");
            }
            else {
                pop(stack);
            }
        }
        else if (strcmp(op, "Dequeue") == 0) {
            if (isStackEmpty(stack)) {
                printf("-1\n");
            }
            else {
                Queue* topQueue = (Queue*)stack->arr[stack->rear];
                int val = dequeue(topQueue);
                if (isQueueEmpty(topQueue)) {
                    pop(stack);
                }
                printf("%d\n", val);
            }
        }
        else if (strcmp(op, "MaxSumPairs") == 0) {
            int K;
            scanf("%d", &K);
            if (isStackEmpty(stack)) {
                printf("-1\n");
            }
            else {
                Queue* topQueue = (Queue*)stack->arr[stack->rear];
                int count = 0;
                int maxCount = 0;
                int i = topQueue->front;
                int j = topQueue->front;
                int sum = topQueue->arr[i];
                while (j <= topQueue->rear) {
                    if (sum >= K) {
                        count++;
                        maxCount = (count > maxCount) ? count : maxCount;
                        sum -= topQueue->arr[i];
                        i++;
                    }
                    else {
                        j++;
                        if (j <= topQueue->rear) {
                            sum += topQueue->arr[j];
                            count++;
                        }
                    }
                }
                printf("%d\n", maxCount);
                if (isQueueEmpty(topQueue)) {
                    pop(stack);
                }
            }
        }
    }
    
    return 0;
}
