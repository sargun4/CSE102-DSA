#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};

struct node* revknodes(struct node* head, int k) {
    struct node* curr = head;
    struct node* prev = NULL;
    struct node* next = NULL;
    int count = 0;
    /* Reverse first k nodes of the linked list */
    while (curr != NULL && count < k) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
        count++;
    }
    /* Recursively call the revknodes function for the remaining nodes */
    if (next != NULL) {
        head->next = revknodes(next, k);
    }
    /* Return the new head of the reversed list */
    return prev;
}
float findMedian(struct node* head) {
    struct node* slow = head;
    struct node* fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    if (fast == NULL) {//odd no of nodes
        return slow->data;
    } else { //even no of nodes
        return (float)(slow->data + slow->next->data) / 2;
    }
}
int main() {
    struct node* head = NULL;
    struct node* tail = NULL;
    for (int i = 1; i <= 7; i++) {
        struct node* temp = (struct node*) malloc(sizeof(struct node));
        temp->data = i;
        temp->next = NULL;
        if (head == NULL) {
            head = temp;
            tail = temp;
        } else {
            tail->next = temp;
            tail = temp;
        }
    }
    head = revknodes(head, 3);
    float median = findMedian(head);
    printf("The median of the linked list is %.2f\n", median);

    return 0;
}
