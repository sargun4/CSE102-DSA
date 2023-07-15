#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

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
struct node* mergeSort(struct node* head);
struct node* mergeLists(struct node* l1, struct node* l2);

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
    if (l1 != NULL) {
        curr->next = l1;
    } else {
        curr->next = l2;
    }
    
    return head;
}

int main() {
    struct node* head = (struct node*)malloc(sizeof(struct node));
    head->data = 1;
    head->next = (struct node*)malloc(sizeof(struct node));
    head->next->data = 2;
    head->next->next = (struct node*)malloc(sizeof(struct node));
    head->next->next->data = 3;
    head->next->next->next = (struct node*)malloc(sizeof(struct node));
    head->next->next->next->data = 4;
    head->next->next->next->next = (struct node*)malloc(sizeof(struct node));
    head->next->next->next->next->data = 5;
    head->next->next->next->next->next = NULL;
    
    int k = 2;
    
    struct node* reversed = reverseKNodes(head, k);
    while (reversed != NULL) {
        printf("%d ", reversed->data);
        reversed = reversed->next;
    }printf("\n");
    struct node* sorted = mergeSort(head);
    while (sorted != NULL) {
        printf("%d ", sorted->data);
        sorted = sorted->next;
    }return 0;
}
