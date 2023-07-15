#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
struct node {
    int data;
    struct node* next;
};
void removeDuplicates(struct node* head) {
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
void printList(struct node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");}
void rotate(struct node** head_ref, int k){
    if (k == 0)
        return;
    struct node* current = *head_ref;
    // current will either point to kth or NULL after this
    // loop. current will point to node 40 in the above
    // example
    int count = 1;
    while (count < k && current != NULL) {
        current = current->next;
        count++;
    }
    // If current is NULL, k is greater than or equal to
    // count of nodes in linked list. Don't change the list
    // in this case
    if (current == NULL)
        return;
    // current points to kth node. Store it in a variable.
    // kthNode points to node 40 in the above example
    struct node* kthNode = current;
    // current will point to last node after this loop
    // current will point to node 60 in the above example
    while (current->next != NULL)
        current = current->next;
    // Change next of last node to previous head
    // Next of 60 is now changed to node 10
    current->next = *head_ref;
    // Change head to (k+1)th node
    // head is now changed to node 50
    *head_ref = kthNode->next;
    // change next of kth node to NULL
    // next of 40 is now NULL
    kthNode->next = NULL;
}
struct node* createnode( int data){
    struct node *temp=malloc(sizeof(struct node));
    temp->data=data;
    temp->next=NULL;
    return temp;
}
struct node* insertatend(struct node* head,int data){
    struct node* p=malloc(sizeof(struct node));
    struct node* temp=head;
    while(temp->next!=NULL){
        temp=temp->next;
    }
    p->data=data;
    temp->next=p;
    return head;
}
int main() {
    // Create a linked list with duplicates
    struct node* head =createnode(1);
    head=insertatend(head,2);
    head=insertatend(head,3);
    head=insertatend(head,4);
    head=insertatend(head,5);
    head=insertatend(head,2);
    head=insertatend(head,3);
    printf("Original list: ");
    printList(head);
    removeDuplicates(head);
    printf("List after removing duplicates: ");
    printList(head);
    printf("\n");
    // Rotate the linked list by 4 places
    rotate(&head, 4);
    // Print the rotated linked list
    printf("SLL after rotating by 4 places: ");
    printList(head);
    return 0;
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
