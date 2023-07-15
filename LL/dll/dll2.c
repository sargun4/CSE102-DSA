#include <stdio.h>
#include <stdlib.h>
struct node {
    int data;
    struct node* prev;
    struct node* next;
};
struct node* createNode(int data) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = data;
    temp->prev=temp->next = NULL;
    return temp;
}
void insertNode(struct node** head, int data) {
    struct node* temp = createNode(data);
    if(*head == NULL) {
        *head = temp;
        return;
    }
    struct node* current = *head;
    while(current->next != NULL) {
        current = current->next;
    }
    current->next = temp;
    temp->prev = current;
}
void insertAtEnd(struct node** head_ref, int new_data) {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    new_node->data = new_data;
    new_node->next = NULL;
    if (*head_ref == NULL) {
        new_node->prev = NULL;
        *head_ref = new_node;
        return;
    }
    struct node* last = *head_ref;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = new_node;
    new_node->prev = last;
}

void insertAtPosition(struct node** head_ref, int new_data, int position) {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    new_node->data = new_data;
    struct node* current = *head_ref;
    for (int i = 1; i < position && current != NULL; i++) {
        current = current->next;
    }
    if (current == NULL) {
        printf("Invalid position\n");
        return;
    }
    new_node->prev = current->prev;
    new_node->next = current;
    current->prev->next = new_node;
    current->prev = new_node;
}
struct node* search(struct node* head, int key) {
    struct node* current = head;
    while (current != NULL && current->data != key) {
        current = current->next;
    }
    return current;
}
int length(struct node* head) {
    int count = 0;
    struct node* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}
struct node* merge(struct node* list1, struct node* list2) {
    if (list1 == NULL) {
        return list2;
    }
    if (list2 == NULL) {
        return list1;
    }
    struct node* result = NULL;
    if (list1->data <= list2->data) {
        result = list1;
        result->next = merge(list1->next, list2);
        result->next->prev = result;
    } else {
        result = list2;
        result->next = merge(list1, list2->next);
        result->next->prev = result;
    }
    return result;
}
struct node* split(struct node** head_ref, int position) {
    struct node* current = *head_ref;
    int count = 1;
    while (count < position && current != NULL) {
        current = current->next;
        count++;
    }
    if (current == NULL) {
        return NULL;
    }
    struct node* second_half = current->next;
    if (second_half != NULL) {
        second_half->prev = NULL;
    }
    current->next = NULL;
    return second_half;
}

void printListBackward(struct node* tail) {
    struct node* current = tail;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->prev;
    }
    printf("\n");
}
void sortList(struct node** head) {
    struct node* current = *head;
    struct node* index = NULL;
    int temp;
    if(*head == NULL) {
        return;
    }
    else {
        while(current != NULL) {
            index = current->next;
            while(index != NULL) {
                if(current->data > index->data) {
                    temp = current->data;
                    current->data = index->data;
                    index->data = temp;
                }
                index = index->next;
            }
            current = current->next;
        }
    }
}
void findNthNodeFromEnd(struct node* head, int n) {
    int len = 0;
    struct node* temp = head;
    while(temp != NULL) {
        len++;
        temp = temp->next;
    }
    if(n > len) {
        printf("Error: List length is smaller than %d\n", n);
        return;
    }
    temp = head;
    for(int i=0; i<len-n; i++) {
        temp = temp->next;
    }
    printf("struct node at position %d from end is %d\n", n, temp->data);
}
void deleteNode(struct node** head, struct node* delNode) {
    if (*head == NULL || delNode == NULL) {
        return;
    }
    //if the node to be deleted is the head
    if (*head == delNode) {
        *head = delNode->next;
    }
    //update the next node's prev pointer
    if (delNode->next != NULL) {
        delNode->next->prev = delNode->prev;
    }
    //update the prev node's next pointer
    if (delNode->prev != NULL) {
        delNode->prev->next = delNode->next;
    }
    
    //free memory of the deleted node
    free(delNode);
}
struct node* revknodes(struct node* head, int k) {
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
        head->next = revknodes(next, k);
        head->next->prev = head;
    }    
    //prev is the new head of the input list
    return prev;
}

void reverseDLL(struct node** head_ref) {
    struct node* temp = NULL;
    struct node* current = *head_ref;
    // swap next and prev pointers of each node
    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    //update the head pointer to the new first node
    if (temp != NULL) {
        *head_ref = temp->prev;
    }
}
void printList(struct node* node) {
    while (node != NULL) {
        printf("%d <-> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}
void bubbleSortDesc(struct node** head_ref) {
    if (*head_ref == NULL || (*head_ref)->next == NULL) {
        return;
    }
    struct node *current, *idx;
    int swapped;
    do {
        swapped = 0;
        current = *head_ref;
        while (current->next != NULL) {
            idx = current->next;
            if (current->data < idx->data) {
                int temp=current->data;
                current->data=idx->data;
                idx->data=temp;
                swapped = 1;
            }
            current = current->next;
        }
    } while (swapped);
}
struct node* findMiddleNode(struct node* head) {
    struct node *slow_ptr = head, *fast_ptr = head;
    while (fast_ptr != NULL && fast_ptr->next != NULL) {
        slow_ptr = slow_ptr->next;
        fast_ptr = fast_ptr->next->next;
    }
    return slow_ptr;
}
struct node* merge(struct node* left, struct node* right) {
    if (left == NULL) {
        return right;
    }
    if (right == NULL) {
        return left;
    }
    struct node* result = NULL;
    if (left->data <= right->data) {
        result = left;
        result->next = merge(left->next, right);
    } else {
        result = right;
        result->next = merge(left, right->next);
    }
    result->next->prev = result;
    result->prev = NULL;
    return result;
}

struct node* mergeSort(struct node* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }
    struct node* middle = findMiddleNode(head);
    struct node* second_half = middle->next;
    middle->next = NULL;
    second_half->prev = NULL;
    struct node* left = mergeSort(head);
    struct node* right = mergeSort(second_half);
    return merge(left, right);
}
void rotate(struct node** head_ref, int k) {
    if (k == 0) {
        return;
    }
    struct node* current = *head_ref;
    int count = 1;
    while (count < k && current != NULL) {
        current = current->next;
        count++;
    }
    if (current == NULL) {
        return;
    }
    struct node* kth_node = current;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = *head_ref;
    (*head_ref)->prev = current;
    *head_ref = kth_node->next;
    (*head_ref)->prev = NULL;
    kth_node->next = NULL;
}

int main(){
    struct node* head = createNode(1);
    insertNode(&head, 10);
    insertNode(&head, 30);
    insertNode(&head, 20);
    insertNode(&head, 50);
    insertNode(&head, 40);

    printf("Original List: ");
    printList(head);

    findNthNodeFromEnd(head, 2);

    sortList(&head);

    printf("Sorted List(ASC): ");
    printList(head);

    reverseDLL(&head);
    printList(head);
    
    head = revknodes(head, 3);
    printf("Reversed List in groups of %d: ",3);
    printList(head);
    
    printf("Sorted List(DESC): ");
    bubbleSortDesc(&head);
    printList(head);
    return 0;
}