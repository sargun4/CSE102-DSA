#include <stdio.h>
#include <stdlib.h>
struct node {
    int data;
    struct node *prev;
    struct node *next;
};
void insertatfront(struct node **head, int data) {
    struct node *temp = (struct node*)malloc(sizeof(struct node));
    temp->data = data;
    temp->prev = NULL;
    temp->next = *head;
    if(*head != NULL) {
        (*head)->prev = temp;
    }
    *head = temp;
}

void insertAtEnd(struct node **head, int data) {
    struct node *temp = (struct node*)malloc(sizeof(struct node));
    temp->data = data;
    temp->next = NULL;

    if(*head == NULL) {
        temp->prev = NULL;
        *head = temp;
        return;
    }

    struct node *p = *head;
    while(p->next != NULL) {
        p = p->next;
    }

    p->next = temp;
    temp->prev = p;
}

void deleteNode(struct node **head, struct node *delNode) {
    if(*head == NULL || delNode == NULL) {
        return;
    }

    if(*head == delNode) {
        *head = delNode->next;
    }

    if(delNode->next != NULL) {
        delNode->next->prev = delNode->prev;
    }

    if(delNode->prev != NULL) {
        delNode->prev->next = delNode->next;
    }

    free(delNode);
}
void printList(struct node *node) {
    while(node != NULL) {
        printf("%d <-> ", node->data);
        node = node->next;
    }printf("NULL\n");
}
void reverseDLL(struct node** head_ref) {
    struct node* temp = NULL;
    struct node* current = *head_ref;
    
    /* swap next and prev pointers of each node */
    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    
    /* set the new head of the list */
    if (temp != NULL) {
        *head_ref = temp->prev;
    }
}
struct node* reverseKNodes(struct node* head, int k) {
    struct node* current = head;
    struct node* next = NULL;
    struct node* prev = NULL;
    int count = 0;
    while (current != NULL && count < k) {
        next = current->next;
        current->next = prev;
        current->prev = next;
        prev = current;
        current = next;
        count++;
    }
    if (next != NULL) {
        head->next = reverseKNodes(next, k);
        head->next->prev = head;
    }  
    /* prev is the new head of the input list */
    return prev;
}


// ITER
int getCount(struct node* head){
    int count = 0; 
    struct node* current = head; 
    while (current != NULL) {
        count++;
        current = current->next; }
    return count;
}
// // REC
// // T-O(N), S-O(N)
// int getCount(struct node* head){
//     if (head == NULL) {
//         return 0;
//     }else {
//         return 1 + getCount(head->next);
//     }
// }
// // T-O(N), S-O(1)
// int getCount(struct node* head, int count = 0){
//     if (head == NULL)
//         return count;
//     return getCount(head->next, count + 1);
// }


/* Function to swap two nodes in a doubly linked list */
void swapNodes(struct node** head_ref, struct node* node1, struct node* node2) {
    /* if nodes are same or either of them is null, do nothing */
    if (node1 == node2 || node1 == NULL || node2 == NULL) {
        return;
    }
    
    /* swap the data of the nodes */
    int temp = node1->data;
    node1->data = node2->data;
    node2->data = temp;
    
    /* update the links of the nodes */
    if (node1->prev == NULL) {
        *head_ref = node1;
    }
    if (node2->next == NULL) {
        *head_ref = node2;
    }
    if (node1->next == node2) {
        node1->next = node2->next;
        node2->prev = node1->prev;
        node1->prev = node2;
        node2->next = node1;
        if (node1->next != NULL) {
            node1->next->prev = node1;
        }
        if (node2->prev != NULL) {
            node2->prev->next = node2;
        }
    } else {
        node2->next = node1->next;
        node1->prev = node2->prev;
        node2->prev = node1;
        node1->next = node2;
        if (node2->next != NULL) {
            node2->next->prev = node2;
        }
        if (node1->prev != NULL) {
            node1->prev->next = node1;
        }
    }
}

/* Function to perform bubble sort on a doubly linked list */
void bubbleSortDLL(struct node** head_ref) {
    int swapped = 1;
    struct node* ptr1 = NULL;
    struct node* ptr2 = NULL;
    struct node* end = NULL;
    
    /* if list is empty or has only one node, do nothing */
    if (*head_ref == NULL || (*head_ref)->next == NULL) {
        return;
    }
    
    /* loop until no swaps are performed */
    while (swapped) {
        swapped = 0;
        ptr1 = *head_ref;
        /* loop from head to end */
        while (ptr1->next != end) {
            ptr2 = ptr1->next;
            /* if the nodes are in wrong order, swap them */
            if (ptr1->data > ptr2->data) {
                swapNodes(head_ref, ptr1, ptr2);
                swapped = 1;
            } else {
                ptr1 = ptr1->next;
            }
        }
        end = ptr1;
    }
}

void reverse(struct node** head_ref){
    struct node* temp = NULL;
    struct node* current = *head_ref;
    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    if (temp != NULL)
        *head_ref = temp->prev;
}

int GetNth(struct node* head, int n){
    if (head == NULL)
        return -1;
    if (n == 0)
        return head->data;
    return GetNth(head->next, n - 1);
}

int main() {
    struct node *head = NULL;
    insertAtEnd(&head, 1);
    insertatfront(&head, 2);
    insertAtEnd(&head, 3);
    insertatfront(&head, 4);

    printf("Doubly linked list: ");
    printList(head);
    printf("Element at index 3 is %d", GetNth(head, 3));
    // bubbleSortDLL(&head);
    // printf("Sorted list: ");
    // printList(head);
    
    // revKNodes(&head,2);
    // printList(head);

    deleteNode(&head, head);
    deleteNode(&head, head->next);

    printf("\nDoubly linked list after deletion: ");
    printList(head);
    return 0;
}
// #include <stdio.h>
// #include <stdlib.h>

// struct node {
//     int data;
//     struct node* prev;
//     struct node* next;
// };

// struct node* create_node(int data) {
//     struct node* temp = malloc(sizeof(struct node));
//     temp->data = data;
//     temp->prev = NULL;
//     temp->next = NULL;
//     return temp;
// }
// void display(struct node* head) {
//     struct node* temp = head;
//     while (temp != NULL) {
//         printf("%d <-> ", temp->data);
//         temp = temp->next;
//     }
//     printf("NULL\n");
// }
// int main() {
//     struct node* head = create_node(1);
//     head->next=create_node(2);
//     head->next->next=create_node(0);
//     display(head);
//     return 0;
// }

