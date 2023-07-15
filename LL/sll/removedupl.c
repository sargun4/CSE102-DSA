#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
struct node {
    int data;
    struct node* next;
};
void removeDuplicates(struct node* head);
int main() {
    // Create a linked list with duplicates
    struct node* head = malloc(sizeof(struct node));
    head->data = 1;
    head->next = malloc(sizeof(struct node));
    head->next->data = 1;
    head->next->next = malloc(sizeof(struct node));
    head->next->next->data = 2;
    head->next->next->next = malloc(sizeof(struct node));
    head->next->next->next->data = 2;
    head->next->next->next->next = NULL;
    // Print the original linked list
    struct node* current = head;
    printf("Original linked list: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
    // Remove duplicates from the linked list
    removeDuplicates(head);
    // Print the modified linked list
    current = head;
    printf("SLL after removing duplicates: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
    // Free memory
    current = head;
    while (current != NULL) {
        struct node* temp = current;
        current = current->next;
        free(temp);
    }
    return 0;
}
//only for sorted LL
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
// This function rotates a linked list counter-clockwise and
// updates the head. The function assumes that k is smaller
// than size of linked list. It doesn't modify the list if
// k is greater than or equal to size
void rotate(struct node** head_ref, int k){
    if (k == 0)
        return;
    struct node* current = *head_ref;
    int count = 1;
    while (count < k && current != NULL) {
        current = current->next;
        count++;
    }
    if (current == NULL)
        return;
    struct node* kthNode = current;
    while (current->next != NULL)
        current = current->next;
    current->next = *head_ref;
    *head_ref = kthNode->next;
    kthNode->next = NULL;
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
struct node* reverseListRecursive(struct node* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }
    struct node* newHead = reverseListRecursive(head->next);
    head->next->next = head;
    head->next = NULL;
    return newHead;
}
struct node* middleNode(struct node* head) {
    if (head == NULL) {
        return NULL;
    }
    struct node *slow = head, *fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
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

struct node* reverseKNodes(struct node* head, int k) {
    struct node* curr = head;
    struct node* prev = NULL;
    struct node* next = NULL;
    int count = 0;
    while (curr != NULL && count < k) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
        count++;
    }
    if (next != NULL) {
        head->next = reverseKNodes(next, k);
    }
    return prev;
}

struct node* mergeSort(struct node* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }
    struct node* slow = head;
    struct node* fast = head->next;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    struct node* mid = slow->next;
    slow->next = NULL;
    struct node* left = mergeSort(head);
    struct node* right = mergeSort(mid);   
    return mergeLists(left, right);
}

struct node* mergeLists(struct node* l1, struct node* l2) {
    if (l1 == NULL) {
        return l2;
    }
    if (l2 == NULL) {
        return l1;
    }
    struct node* head;
    struct node* curr;
    if (l1->data < l2->data) {
        head = l1;
        l1 = l1->next;
    } else {
        head = l2;
        l2 = l2->next;
    }
    curr = head;
    while (l1 != NULL && l2 != NULL) {
        if (l1->data < l2->data) {
            curr->next = l1;
            l1 = l1->next;
        } else {
            curr->next = l2;
            l2 = l2->next;
        }
        curr = curr->next;
    }
    if (l1 == NULL) {
        curr->next = l2;
    } else {
        curr->next = l1;
    }
    return head;
}
void divideByIndex(struct node* head) {
    struct node* curr = head;
    int index = 1;
    
    while (curr != NULL) {
        curr->data /= index;
        curr = curr->next;
        index++;
    }
}

struct node *kAltReverse(struct node *head, int k){
    struct node* current = head;
    struct node* next;
    struct node* prev = NULL;
    int count = 0;
    /*1) reverse first k nodes of the linked list */
    while (current != NULL && count < k){
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
        count++;
    }
    /* 2) Now head points to the kth node.
    So change next  of head to (k+1)th node*/
    if(head != NULL)
        head->next = current;
    /* 3) We do not want to reverse next k
       nodes. So move the current
        pointer to skip next k nodes */
    count = 0;
    while(count < k-1 && current != NULL )
    {
    current = current->next;
    count++;
    }
    /* 4) Recursively call for the list
    starting from current->next. And make
    rest of the list as next of first node */
    if(current != NULL)
    current->next = kAltReverse(current->next, k);
    /* 5) prev is new head of the input list */
    return prev;
}
