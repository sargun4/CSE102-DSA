#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function to insert a node at the end of the linked list
void insert(Node** head, int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    if (*head == NULL) {
        *head = new_node;
    } else {
        Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

// Function to find the median of all values in a linked list
float findMedian(Node* head) {
    int count = 0;
    Node* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    int middle = count / 2;
    current = head;
    if (count % 2 == 0) {
        for (int i = 1; i < middle; i++) {
            current = current->next;
        }
        return (float)(current->data + current->next->data) / 2.0;
    } else {
        for (int i = 1; i <= middle; i++) {
            current = current->next;
        }
        return (float)current->data;
    }
}

int main() {
    Node* head = NULL;
    insert(&head, 1);
    insert(&head, 2);
    insert(&head, 3);
    insert(&head, 4);
    insert(&head, 5);
    printf("Median of the linked list is: %.2f\n", findMedian(head));
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function to insert a node at the end of the linked list
void insert(Node** head, int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    if (*head == NULL) {
        *head = new_node;
    } else {
        Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

// Function to check if two lists are identical
int areIdentical(Node* head1, Node* head2) {
    Node* current1 = head1;
    Node* current2 = head2;
    while (current1 != NULL && current2 != NULL) {
        if (current1->data != current2->data) {
            return 0;
        }
        current1 = current1->next;
        current2 = current2->next;
    }
    return (current1 == NULL && current2 == NULL);
}

int main() {
    Node* head1 = NULL;
    insert(&head1, 1);
    insert(&head1, 2);
    insert(&head1, 3);
    Node* head2 = NULL;
    insert(&head2, 1);
    insert(&head2, 2);
    insert(&head2, 3);
    if (areIdentical(head1, head2)) {
        printf("Lists are identical\n");
    }
    else {
    printf("Lists are not identical\n");
}
return 0;
}
