#include <stdio.h>
#include <stdlib.h>
struct Node {
    int data;
    struct Node* next;
};
void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}
void append(struct Node** head_ref, int data) {
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->next = NULL;
    if (*head_ref == NULL) {
        *head_ref = new_node;
    } else {
        struct Node* current = *head_ref;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}
void rotate(struct Node** head_ref, int k) {
    if (*head_ref == NULL) {
        return;
    }
    int length = 0;
    struct Node* current = *head_ref;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    /* Normalize k so that it is less than the length of the linked list */
    k = k % length;
    if (k == 0) {
        return;
    }
    /* Find the new tail and new head of the linked list */
    int new_tail_index = length - k - 1;
    struct Node* new_tail = *head_ref;
    for (int i = 0; i < new_tail_index; i++) {
        new_tail = new_tail->next;
    }
    struct Node* new_head = new_tail->next;
    /* Make the new tail point to NULL */
    new_tail->next = NULL;
    /* Make the old tail point to the old head */
    struct Node* old_tail = new_head;
    while (old_tail->next != NULL) {
        old_tail = old_tail->next;
    }
    old_tail->next = *head_ref;
    /* Set the new head of the linked list */
    *head_ref = new_head;
}
void deleteNode(struct Node** head_ref, int key) {
    struct Node* current = *head_ref;
    struct Node* previous = NULL;
    while (current != NULL && current->data != key) {
        previous = current;
        current = current->next;
    }
    /* If the node was not found, return */
    if (current == NULL) {
        return;
    }
    /* If the node is the head of the linked list, update the head */
    if (previous == NULL) {
        *head_ref = current->next;
    } else {
        previous->next = current->next;
    }
    /* Free the memory allocated to the node */
    free(current);
}
int findMode(struct Node* head) {
    int mode = head->data;
    int max_count = 1;
    struct Node* current = head;
    int current_count = 1;
    int current_value = head->data;
    while (current->next != NULL) {
        current = current->next;
        if (current->data == current_value) {
            current_count++;
        } else {
            if (current_count > max_count) {
                mode = current_value;
                max_count = current_count;
            }
            current_value = current->data;
            current_count = 1;
        }
    }
    /* Check the last value */
    if (current_count > max_count) {
        mode = current_value;
        max_count = current_count;
    }
    return mode;
}
float findMean(struct Node *head) {
    int sum = 0;
    int count = 0;
    /* Traverse the linked list, adding up the values and counting the nodes */
    struct Node* current = head;
    while (current != NULL) {
        sum += current->data;
        count++;
        current = current->next;
    }
    float mean = (float) sum / count;
    return mean;
}

int findKthSmallest(struct Node *head, int k) {
    int values[k];
    int index = 0;
    /* Traverse the linked list, adding the values to an array */
    struct Node* current = head;
    while (current != NULL) {
        values[index] = current->data;
        index++;
        current = current->next;
    }
    /* Sort the array */
    for (int i = 0; i < k; i++) {
        int min_index = i;
        for (int j = i + 1; j < k; j++) {
            if (values[j] < values[min_index]) {
                min_index = j;
            }
        }
        int temp = values[i];
        values[i] = values[min_index];
        values[min_index] = temp;
    }
    /* Return the kth smallest value */
    return values[k - 1];
}
int main() {
    struct Node* head = NULL;
    append(&head, 1);
    append(&head, 3);
    append(&head, 5);
    append(&head, 2);
    append(&head, 5);
    append(&head, 5);
    append(&head, 4);
    printf("Original linked list:\n");
    printList(head);
    /* Rotate the linked list by 3 nodes */
    rotate(&head, 3);
    printf("Linked list after rotating by 3:\n");
    printList(head);
    deleteNode(&head, 3);
    printf("Linked list after deleting 3:\n");
    printList(head);
    int mode = findMode(head);
    printf("Mode of the linked list: %d\n", mode);
    float mean = findMean(head);
    printf("Mean of the linked list: %.2f\n", mean);
    int k = 3;
    int kth_smallest = findKthSmallest(head, k);
    printf("%dth smallest element in the linked list: %d\n", k, kth_smallest);
    return 0;
}
