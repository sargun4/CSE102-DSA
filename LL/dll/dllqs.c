// Reversing a doubly linked list recursively
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// Function to insert a node at the end of the doubly linked list
void insert(Node** head, int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = NULL;
    if (*head == NULL) {
        *head = new_node;
    } else {
        Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
        new_node->prev = current;
    }
}
// Function to recursively reverse a doubly linked list
Node* reverse(Node* current) {
    if (current == NULL) {
        return NULL;
    }
    Node* temp = current->prev;
    current->prev = current->next;
    current->next = temp;
    if (current->prev == NULL) {
        return current;
    }
    return reverse(current->prev);
}
// Function to iteratively reverse a doubly linked list
Node* reverse(Node* head) {
    Node* current = head;
    Node* temp;
    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    if (temp != NULL) {
        head = temp->prev;
    }
    return head;
}
/*Algorithm to remove duplicates from an unsorted doubly linked list:

Create an empty hash table to keep track of the unique elements in the list.
Traverse the doubly linked list and for each node, do the following:
a. Check if the current node's data is already in the hash table. If it is, remove the node from the list.
b. If the data is not in the hash table, add it to the hash table.
Return the head of the updated doubly linked list.

Algorithm to sort a doubly linked list:

If the doubly linked list is empty or has only one element, return the head.
Divide the list into two sublists of roughly equal size by traversing the list with two pointers. Use the slow pointer to find the midpoint of the list.
Recursively sort the two sublists.
Merge the two sorted sublists using a merge function, which takes the heads of the two sublists as input and returns the head of the merged list.
Return the head of the merged list.
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *prev;
    struct node *next;
} Node;

Node *remove_duplicates(Node *head) {
    // Create a hash table to store unique elements
    int table[100] = {0};
    
    Node *current = head;
    while (current != NULL) {
        // Check if current node's data is in hash table
        if (table[current->data] == 1) {
            // Remove the node from the list
            Node *prev = current->prev;
            Node *next = current->next;
            if (prev != NULL) {
                prev->next = next;
            }
            if (next != NULL) {
                next->prev = prev;
            }
            if (current == head) {
                head = next;
            }
            free(current);
        } else {
            // Add the data to the hash table
            table[current->data] = 1;
        }
        current = current->next;
    }
    return head;
}

void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}
int main() {
    Node* head = NULL;
    insert(&head, 1);
    insert(&head, 2);
    insert(&head, 3);
    insert(&head, 4);
    insert(&head, 5);
    printf("Original doubly linked list: ");
    printList(head);
    head = reverse(head);
    printf("Reversed doubly linked list: ");
    printList(head);
    return 0;
}
