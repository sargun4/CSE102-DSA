#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
    int data;
    struct node* next;
};
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
struct node* middleNode(struct node* head) {
    struct node* slow = head;
    struct node* fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}
struct node* rev(struct node* head){
    struct node* curr = head;
    struct node* prev = NULL;
    struct node* next = NULL;
    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
    return head;
}
bool isPalindrome(struct node* head) {
    if (head == NULL || head->next == NULL) {
        return true;
    }
    struct node* middle = middleNode(head);
    struct node* secondHalf = rev(middle);
    struct node* p1 = head, *p2 = secondHalf;
    while (p2 != NULL) {
        if (p1->data != p2->data) {
            rev(secondHalf);
            return false;
        }
        p1 = p1->next;
        p2 = p2->next;
    }
    rev(secondHalf);
    return true;
}
int main() {
    // Create a linked list: 1 -> 2 -> 3 -> 2 -> 1
    struct node* head = NULL;
    insertAtEnd(&head, 1);
    insertAtEnd(&head, 2);
    insertAtEnd(&head, 3);
    insertAtEnd(&head, 2);
    insertAtEnd(&head, 1);
    if (isPalindrome(head)) {
        printf("The linked list is a palindrome.\n");
    }
    else {
        printf("The linked list is not a palindrome.\n");
    }
    return 0;
}
