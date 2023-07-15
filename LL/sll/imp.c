#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
struct node {
    int data;
    struct node *next;
};

struct node* insert_at_beginning(struct node* head, int data) {
    // Create a new node
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = head;
    // Return the new head of the list
    return new_node;
}
struct node* insert_at_end(struct node* head, int data) {
    // Create a new node
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = NULL;

    // If the list is empty, the new node becomes the head of the list
    if (head == NULL) {
        return new_node;
    }

    // Traverse the list to the end
    struct node* current_node = head;
    while (current_node->next != NULL) {
        current_node = current_node->next;
    }

    // Attach the new node to the end of the list
    current_node->next = new_node;

    // Return the head of the list
    return head;
}
struct node* insert_at_position(struct node* head, int data, int position) {
    // Create a new node
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    new_node->data = data;

    // If the list is empty or position = 0, the new node becomes the head of the list
    if (head == NULL || position == 0) {
        new_node->next = head;
        return new_node;
    }

    // Traverse the list to the node just before the insertion position
    struct node* current_node = head;
    int i;
    for (i = 0; i < position-1 && current_node->next != NULL; i++) {
        current_node = current_node->next;
    }

    // If position is out of range, return the original head of the list
    if (i < position-1) {
        return head;
    }

    // Attach the new node to the list
    new_node->next = current_node->next;
    current_node->next = new_node;

    // Return the head of the list
    return head;
}

// Function to insert a new node at the end of the linked list
void insertAtEnd(struct node **head, int data) {
    struct node *newNode = (struct node *) malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = NULL;
    
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    
    struct node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->next = newNode;
}

// Function to insert a new node at a specified position in the linked list
void insertAtPosition(struct node **head, int data, int position) {
    if (position < 1) {
        printf("Invalid position\n");
        return;
    }
    
    struct node *newNode = (struct node *) malloc(sizeof(struct node));
    newNode->data = data;
    
    if (position == 1) {
        newNode->next = *head;
        *head = newNode;
        return;
    }
    
    struct node *current = *head;
    for (int i = 1; i < position - 1 && current != NULL; i++) {
        current = current->next;
    }
    
    if (current == NULL) {
        printf("Invalid position\n");
        return;
    }
    
    newNode->next = current->next;
    current->next = newNode;
}

// Function to delete the first node of the linked list
void deleteFirstNode(struct node **head) {
    if (*head == NULL) {
        printf("The list is already empty\n");
        return;
    }
    struct node *temp = *head;
    *head = (*head)->next;
    free(temp);
}

// Function to delete the last node of the linked list
void deleteLastNode(struct node **head) {
    if (*head == NULL) {
        printf("The list is already empty\n");
        return;
    }
    
    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }
    
    struct node *current = *head;
    while (current->next->next != NULL) {
        current = current->next;
    }
    
    free(current->next);
    current->next = NULL;
}
//for BST
/*struct node *delete_node(struct node *root, char data) {
    // If the root is NULL, the tree is empty, so return the root
    if (root == NULL) {
        return root;
    }
    // If the data is less than the root's data, the node to be deleted is in the left subtree
    else if (data < root->data) {
        root->left = delete_node(root->left, data); // Recursively delete the node from the left subtree
    }
    // If the data is greater than the root's data, the node to be deleted is in the right subtree
    else if (data > root->data) {
        root->right = delete_node(root->right, data); // Recursively delete the node from the right subtree
    }
    // If the root's data matches the data to be deleted, we have found the node to be deleted
    else {
        // If the node has no left child, we replace it with its right child (which may be NULL)
        if (root->left == NULL) {
            struct node *temp = root->right; // Save the right child in a temporary variable
            free(root); // Free the memory occupied by the node to be deleted
            return temp; // Return the right child, which takes the place of the deleted node
        }
        // If the node has no right child, we replace it with its left child
        else if (root->right == NULL) {
            struct node *temp = root->left; // Save the left child in a temporary variable
            free(root); // Free the memory occupied by the node to be deleted
            return temp; // Return the left child, which takes the place of the deleted node
        }
        // If the node has two children, we replace it with the inorder successor (smallest node in the right subtree)
        struct node *temp = root->right; // Start with the right child of the node to be deleted
        while (temp->left != NULL) {
            temp = temp->left; // Traverse the left subtree of the right child to find the inorder successor
        }
        root->data = temp->data; // Replace the data of the node to be deleted with the data of the inorder successor
        root->right = delete_node(root->right, temp->data); // Recursively delete the inorder successor from the right subtree
    }
    return root; // Return the modified root of the tree
}
*/
// Function to delete a node at a specified position in the linked list
void deleteNodeAtPosition(struct node **head, int position) {
    if (position < 1) {
        printf("Invalid position\n");
        return;
    }
    if (*head == NULL) {
        printf("The list is already empty\n");
        return;
    }
    
    if (position == 1) {
        struct node *temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }
    
    struct node *current = *head;
    for (int i = 1; i < position - 1 && current != NULL; i++) {
        current = current->next;
    }
    
    if (current ==NULL) {
        printf("Invalid position\n");
        return;
        }
    struct node *temp = current->next;
    current->next = current->next->next;
    free(temp);
}

void printList(struct node *head) {
    struct node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}
// Function to search for a node with a given value in the linked list
int search(struct node *head, int data) {
    int position = 1;
    struct node *current = head;
    while (current != NULL) {
        if (current->data == data) {
            return position;
    }
    position++;
    current = current->next;
    }
    return -1;
}
void reverseList(struct node** head) {
    struct node *prev = NULL, *current = *head, *next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}
int getMiddle(struct node* head) {
    struct node *slow = head, *fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow->data;
}
// Check if a linked list is circular (i.e., if the last node points to one of the previous nodes):
bool isCircular(struct node* head) {
    struct node *slow = head, *fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return true;
        }
    }
    return false;
}

//only deletes duplicate elmnts consecutively placed -for sorted LL
void removeDuplicates(struct node* head) {
    struct node *current = head, *nextNode = NULL;
    while (current != NULL && current->next != NULL) {
        if (current->data == current->next->data) {
            nextNode = current->next->next;
            free(current->next);
            current->next = nextNode;
        } else {
            current = current->next;
        }
    }
}

void removeDuplicates1(struct node* start){
    struct node *ptr1, *ptr2, *dup;
    ptr1 = start;
    /* Pick elements one by one */
    while (ptr1 != NULL && ptr1->next != NULL) {
        ptr2 = ptr1;
        /* Compare the picked element with rest
           of the elements */
        while (ptr2->next != NULL) {
            /* If duplicate then delete it */
            if (ptr1->data == ptr2->next->data) {
                /* sequence of steps is important here */
                dup = ptr2->next;
                ptr2->next = ptr2->next->next;
                free(dup);
            }
            else /* This is tricky */
                ptr2 = ptr2->next;
        }
        ptr1 = ptr1->next;
    }
}

void removeDuplicates2(struct node* head) {
    struct node *current = head, *temp = NULL, *prev = NULL;
    while (current != NULL) {
        temp = current->next;
        prev = current;
        while (temp != NULL) {
            if (current->data == temp->data) {
                prev->next = temp->next;
                free(temp);
                temp = prev->next;
            } else {
                prev = temp;
                temp = temp->next;
            }
        }
        current = current->next;
    }
}
 
struct node* mergeSortedLists(struct node* l1, struct node* l2) {
    if (l1 == NULL) {
        return l2;
    }
    if (l2 == NULL) {
        return l1;
    }
    struct node *head = NULL, *tail = NULL;
    if (l1->data <= l2->data) {
        head = l1;
        tail = l1;
        l1 = l1->next;
    } else {
        head = l2;
        tail = l2;
        l2 = l2->next;
    }
    while (l1 != NULL && l2 != NULL) {
        if (l1->data <= l2->data) {
            tail->next = l1;
            tail = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            tail = l2;
            l2 = l2->next;
        }
    }
    if (l1 == NULL) {
        tail->next = l2;
    } else {
        tail->next = l1;
    }
    return head;
}
void detectAndRemoveLoop(struct node* head) {
    if (head == NULL || head->next == NULL) {
        return;
    }
    struct node *slow = head, *fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            break;
        }
    }
    if (slow != fast) {
        return;
    }
    slow = head;
    while (slow->next != fast->next) {
        slow = slow->next;
        fast = fast->next;
    }
    fast->next = NULL;
}
struct node* mergeSort(struct node* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }
    struct node *slow = head, *fast = head->next;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    struct node *mid = slow->next;
    slow->next = NULL;
    struct node *left = mergeSort(head);
    struct node *right = mergeSort(mid);
    return mergeSortedLists(left, right);
}
void deleteList(struct node* head) {
    struct node* current = head;
    while (current != NULL) {
        struct node* next = current->next;
        free(current);
        current = next;
    }
}

struct node* rotateList(struct node* head, int k) {
    if (head == NULL || head->next == NULL || k == 0) {
        return head;
    }
    int len = 1;
    struct node* tail = head;
    while (tail->next != NULL) {
        tail = tail->next;
        len++;
    }
    k %= len;
    if (k == 0) {
        return head;
    }
    struct node* newTail = head;
    for (int i = 1; i < len - k; i++) {
        newTail = newTail->next;
    }
    struct node* newHead = newTail->next;
    newTail->next = NULL;
    tail->next = head;
    return newHead;
}
 
bool isPalindrome(struct node* head) {
    if (head == NULL || head->next == NULL) {
        return true;
    }
    struct node* middle = middleNode(head);
    struct node* secondHalf = reverseListRecursive(middle);
    struct node* p1 = head, *p2 = secondHalf;
    while (p2 != NULL) {
        if (p1->data != p2->data) {
            reverseListRecursive(secondHalf);
            return false;
        }
        p1 = p1->next;
        p2 = p2->next;
    }
    reverseListRecursive(secondHalf);
    return true;
}

struct node* removeNthFromEnd(struct node* head, int n) {
    if (head == NULL) {
        return NULL;
    }
    struct node* dummy = (struct node*)malloc(sizeof(struct node));
    dummy->next = head;
    struct node *fast = dummy, *slow = dummy;
    for (int i = 1; i <= n + 1; i++) {
        fast = fast->next;
    }
    while (fast != NULL) {
        slow = slow->next;
        fast = fast->next;
    }
    slow->next = slow->next->next;
    return dummy->next;
}

struct node* reverseListIterative(struct node* head) {
    struct node *prev = NULL, *current = head;
    while (current != NULL) {
        struct node* next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}

struct node* reverseListRecursive(struct node* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }
    struct node* newHead = reverseListRecursive(head->next);
    head->next->next = head;
    head->next = NULL;
    return newHead;
}

struct node* reverseBetween(struct node* head, int m, int n) {
    if (head == NULL || head->next == NULL || m == n) {
        return head;
    }
    struct node* dummy = (struct node*)malloc(sizeof(struct node));
    dummy->next = head;
    struct node* pre = dummy;
    for (int i = 1; i < m; i++) {
        pre = pre->next;
    }
    head = pre->next;
    for (int i = m; i < n; i++) {
        struct node* temp = head->next;
        head->next = temp->next;
        temp->next = pre->next;
        pre->next = temp;
    }
    return dummy->next;
}

int main() {
    struct node *head = NULL;
    insertAtBeginning(&head, 5);
    insertAtEnd(&head, 10);
    insertAtPosition(&head, 7, 2);
    insertAtPosition(&head, 8, 3);

    printf("Linked list: ");
    printList(head);

    deleteFirstNode(&head);
    deleteLastNode(&head);
    deleteNodeAtPosition(&head, 2);

    printf("Linked list after deletion: ");
    printList(head);

    int position = search(head, 8);
    if (position == -1) {
        printf("The value 8 is not in the list\n");
    } else {
        printf("The value 8 is at position %d in the list\n", position);
    }
    return 0;
}