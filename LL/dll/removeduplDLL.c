#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *prev;
    struct node *next;
};

struct node* remove_duplicates(struct node *head) {
    struct node *current = head;
    struct node *prev, *next;
    int hash_table[1000] = {0};

    while (current != NULL) {
        if (hash_table[current->data] == 1) {
            // Remove the node from the doubly linked list
            prev = current->prev;
            next = current->next;
            if (prev != NULL)
                prev->next = next;
            if (next != NULL)
                next->prev = prev;
            if (current == head)
                head = next;
            free(current);
        } else {
            // Add the data to the hash table
            hash_table[current->data] = 1;
        }
        current = current->next;
    }
    return head;
}


struct node* merge(struct node *first, struct node *second) {
    struct node *result = NULL;
    if (first == NULL)
        return second;
    if (second == NULL)
        return first;

    if (first->data <= second->data) {
        result = first;
        result->next = merge(first->next, second);
        result->next->prev = result;
    } else {
        result = second;
        result->next = merge(first, second->next);
        result->next->prev = result;
    }
    return result;
}

void split(struct node *head, struct node **first, struct node **second) {
    struct node *slow = head;
    struct node *fast = head->next;

    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *first = head;
    *second = slow->next;
    slow->next = NULL;
}
struct node* merge_sort(struct node *head) {
    if (head == NULL || head->next == NULL)
        return head;

    struct node *first, *second;
    split(head, &first, &second);

    first = merge_sort(first);
    second = merge_sort(second);

    return merge(first, second);
}
void print_list(struct node *head) {
    struct node *temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    struct node *head = (struct node*)malloc(sizeof(struct node));
    struct node *second = (struct node*)malloc(sizeof(struct node));
    struct node *third = (struct node*)malloc(sizeof(struct node));
    struct node *fourth = (struct node*)malloc(sizeof(struct node));
    struct node *fifth = (struct node*)malloc(sizeof(struct node));

    head->data = 2;
    head->prev = NULL;
    head->next = second;

    second->data = 4;
    second->prev = head;
    second->next = third;

    third->data = 6;
    third->prev = second;
    third->next = fourth;

    fourth->data = 4;
    fourth->prev = third;
    fourth->next = fifth;

    fifth->data = 8;
    fifth->prev = fourth;
    fifth->next = NULL;

    // Print the original list
    printf("Original list: ");
    struct node *temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");

    // Remove duplicates from the list
    head = remove_duplicates(head);

    // Print the updated list
    printf("Updated list: ");
    temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");


    // Sort the list
    head = merge_sort(head);

    // Print the sorted list
    printf("Sorted list: ");
    print_list(head);


    return 0;
}
