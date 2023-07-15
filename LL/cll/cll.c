#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertAtEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);

    if (*head == NULL) {
        *head = newNode;
        newNode->next = *head;
        return;
    }

    struct Node* temp = *head;

    while (temp->next != *head) {
        temp = temp->next;
    }

    temp->next = newNode;
    newNode->next = *head;
}

void deleteAtEnd(struct Node** head) {
    if (*head == NULL) {
        printf("List is empty.\n");
        return;
    }

    if ((*head)->next == *head) {
        free(*head);
        *head = NULL;
        return;
    }

    struct Node* temp = *head;

    while (temp->next->next != *head) {
        temp = temp->next;
    }

    struct Node* lastNode = temp->next;
    temp->next = *head;
    free(lastNode);
}

void displayList(struct Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct Node* temp = head;

    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != head);

    printf("\n");
}
void cll_sort(struct node** head) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }
    int swapped;
    struct node *curr = *head;
    struct node *temp;
    do {
        swapped = 0;
        while (curr->next != *head) {
            if (curr->data > curr->next->data) {
                temp = curr->next;
                curr->next = temp->next;
                temp->next->prev = curr;
                curr->prev->next = temp;
                temp->prev = curr->prev;
                curr->prev = temp;
                temp->next = curr;
                swapped = 1;
            } else {
                curr = curr->next;
            }
        }
    } while (swapped);
}

int main() {
    struct Node* head = NULL;

    insertAtEnd(&head, 1);
    insertAtEnd(&head, 2);
    insertAtEnd(&head, 3);
    insertAtEnd(&head, 4);
    insertAtEnd(&head, 5);

    displayList(head);

    deleteAtEnd(&head);
    deleteAtEnd(&head);

    displayList(head);

    return 0;
}
