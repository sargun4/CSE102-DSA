#include <stdbool.h>
#include <stdlib.h>
#include<stdio.h>
struct node {
    int data;
    struct node* next;
};
struct node* middleNode(struct node* head) {
    struct node* slow = head;
    struct node* fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}
struct node* reverseListRecursive(struct node* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }
    struct node* rest = reverseListRecursive(head->next);
    head->next->next = head;
    head->next = NULL;
    return rest;
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
void removeduplicates(struct node* head) {
    struct node* curr = head;
    while (curr != NULL) {
        struct node* temp = curr->next;
        struct node* prev = curr;
        while (temp != NULL) {
            if (curr->data == temp->data) {
                prev->next = temp->next;
                free(temp);
                temp = prev->next;
            }
            else {
                prev = temp;
                temp = temp->next;
            }
        }
        curr = curr->next;
    }
}
struct node* createNode(int data) {
    struct node* newNode = (struct node*) malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
void insertAtEnd(struct node** headRef, int data) {
    struct node* newNode = createNode(data);
    if (*headRef == NULL) {
        *headRef = newNode;
    }
    else {
        struct node* curr = *headRef;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = newNode;
    }
}
void display(struct node* head){
    struct node* temp=head;
    while(temp!=NULL){
        printf("%d ",temp->data);
        temp=temp->next;
    }
}
int main() {
    struct node* head = NULL;
    insertAtEnd(&head, 1);
    insertAtEnd(&head, 2);
    insertAtEnd(&head, 3);
    insertAtEnd(&head, 2);
    insertAtEnd(&head, 5);
    printf("before removeduplicates: ");
    display(head);
    printf("\nafter removeduplicates: ");
    removeduplicates(head);
    display(head);
    return 0;
}
