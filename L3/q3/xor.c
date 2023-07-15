#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

void push(Node** head_ref, int new_data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

int getXorK(Node* head, int k) {
    Node* ptr1 = head;
    Node* ptr2 = head;
    int count = 0;

    while (count < k) {
        if (ptr1 == NULL) {
            return -1;
        }
        ptr1 = ptr1->next;
        count++;
    }

    while (ptr1 != NULL) {
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }

    int xor_k = ptr2->data;
    while (ptr2 != NULL) {
        xor_k ^= ptr2->data;
        ptr2 = ptr2->next;
    }
    return xor_k;
}

int main() {
    Node* head = NULL;
    push(&head, 10);
    push(&head, 20);
    push(&head, 30);
    push(&head, 40);
    push(&head, 50);
    push(&head, 60);

    int k = 3;
    int xor_k = getXorK(head, k);

    if (xor_k == -1) {
        printf("K is greater than the length of the linked list.\n");
    } else {
        printf("Xor of last %d nodes of the linked list is %d.\n", k, xor_k);
    }

    return 0;
}
