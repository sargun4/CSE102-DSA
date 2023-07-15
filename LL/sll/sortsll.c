#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} node_t;

void sll_insert(node_t** head, int data) {
    node_t *new_node = (node_t*) malloc(sizeof(node_t));
    new_node->data = data;
    new_node->next = *head;
    *head = new_node;
}

void sll_delete(node_t** head, int data) {
    if (*head == NULL) {
        return;
    }
    if ((*head)->data == data) {
        node_t *temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }
    node_t *cur = *head;
    while (cur->next != NULL) {
        if (cur->next->data == data) {
            node_t *temp = cur->next;
            cur->next = temp->next;
            free(temp);
            return;
        }
        cur = cur->next;
    }
}

node_t* sll_reverse_k(node_t* head, int k) {
    node_t *cur = head, *prev = NULL, *next = NULL;
    int count = 0;
    while (cur != NULL && count < k) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
        count++;
    }
    if (next != NULL) {
        head->next = sll_reverse_k(next, k);
    }
    return prev;
}

void sll_to_cll(node_t** head) {
    if (*head == NULL) {
        return;
    }
    node_t *cur = *head;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = *head;
}

void sll_sort(node_t** head) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }
    int swapped;
    node_t *cur, *temp;
    do {
        swapped = 0;
        cur = *head;
        for (node_t *prev = NULL; cur->next != NULL; prev = cur, cur = cur->next) {
            if (cur->data > cur->next->data) {
                temp = cur->next;
                cur->next = temp->next;
                temp->next = cur;
                if (cur == *head) {
                    *head = temp;
                } else {
                    prev->next = temp;
                }
                cur = temp;
                swapped = 1;
            }
        }
    } while (swapped);
}

 
void sll_remove_duplicates(node_t** head) {
    node_t *current = *head, *temp;
    while (current != NULL && current->next != NULL) {
        if (current->data == current->next->data) {
            temp = current->next;
            current->next = current->next->next;
            free(temp);
        } else {
            current = current->next;
        }
    }
}
void sll_print(node_t* head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}
int main() {
    node_t* head = NULL;
    
    sll_insert(&head, 10);
    sll_insert(&head, 20);
    sll_insert(&head, 30);
    sll_insert(&head, 20);
    sll_insert(&head, 40);
    
    printf("Initial SLL: ");
    sll_print(head);
    
    sll_delete(&head, 20);
    printf("After deleting 20: ");
    sll_print(head);
    
    head = sll_reverse_k(head, 2);
    printf("After reversing every 2 nodes: ");
    sll_print(head);
    
    sll_to_cll(&head);
    printf("SLL converted to CLL: ");
    sll_print(head);
    
    sll_sort(&head);
    printf("After sorting: ");
    sll_print(head);
    
    sll_remove_duplicates(&head);
    printf("After removing duplicates: ");
    sll_print(head);
    
    return 0;
}
