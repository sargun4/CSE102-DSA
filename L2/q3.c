#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 1000000
#define MAX_QUEUE_SIZE 1000000

// queue implementation
typedef struct queue {
    int *arr;
    int front;
    int rear;
    int size;
} queue;

queue *create_queue(int size) {
    queue *q = (queue *) malloc(sizeof(queue));
    q->arr = (int *) malloc(sizeof(int) * size);
    q->front = 0;
    q->rear = -1;
    q->size = 0;
    return q;
}

void enqueue(queue *q, int val) {
    q->rear++;
    q->arr[q->rear] = val;
    q->size++;
}

int dequeue(queue *q) {
    int val = q->arr[q->front];
    q->front++;
    q->size--;
    return val;
}

int is_empty(queue *q) {
    return q->size == 0;
}

// stack implementation
typedef struct stack {
    queue *arr[MAX_STACK_SIZE];
    int top;
} stack;

stack *create_stack() {
    stack *s = (stack *) malloc(sizeof(stack));
    s->top = -1;
    return s;
}

void push(stack *s, int val) {
    queue *q = create_queue(MAX_QUEUE_SIZE);
    enqueue(q, val);
    s->top++;
    s->arr[s->top] = q;
}

void enqueue_to_top(stack *s, int val) {
    if (s->top == -1) {
        push(s, val);
    } else {
        queue *q = s->arr[s->top];
        enqueue(q, val);
    }
}

queue *pop(stack *s) {
    if (s->top == -1) {
        return NULL;
    } else {
        queue *q = s->arr[s->top];
        s->top--;
        return q;
    }
}

int dequeue_from_top(stack *s) {
    queue *q = s->arr[s->top];
    int val = dequeue(q);
    if (is_empty(q)) {
        pop(s);
    }
    return val;
}

int is_stack_empty(stack *s) {
    return s->top == -1;
}

int max_sum_pairs(queue *q, int k) {
    int max_pairs = 0;
    int cur_sum = 0;
    int i = q->front;
    int j = q->front - 1;  // Initialize j to be -1
    while (j < q->rear) {  // Change the termination condition of the loop
        if (cur_sum >= k) {
            max_pairs++;
            cur_sum -= q->arr[i];
            i++;
        } else {
            j++;
            if (j <= q->rear) {
                cur_sum += q->arr[j];
            }
        }
    }
    return max_pairs;
}



int main() {
    int q;
    scanf("%d", &q);
    stack *s = create_stack();
    while (q--) {
        char op[15];
        scanf("%s", op);
        if (strcmp(op, "Push") == 0) {
            int k;
            scanf("%d", &k);
            push(s, k);
        } else if (strcmp(op, "Enqueue") == 0) {
            int k;
            scanf("%d", &k);
            enqueue_to_top(s, k);
        } else if (strcmp(op, "Pop") == 0) {
            if (is_stack_empty(s)) {
                printf("-1\n");
            } else {
                pop(s);
            }
               } else if (strcmp(op, "Dequeue") == 0) {
            if (is_stack_empty(s)) {
                printf("-1\n");
            } else {
                int val = dequeue_from_top(s);
                printf("%d\n", val);
            }
        } else if (strcmp(op, "MaxSumPairs") == 0) {
            if (is_stack_empty(s)) {
                printf("-1\n");
            } else {
                int k;
                scanf("%d", &k);
                queue *q = s->arr[s->top];
                int max_pairs = max_sum_pairs(q, k);
                printf("%d\n", max_pairs);
                pop(s);
            }
        }
    }
    return 0;
}

