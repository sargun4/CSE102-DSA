#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
void display(struct node* head){
    struct node* temp=head;
    while(temp!=NULL){
        printf("%d ",temp->data);
        temp=temp->next;
    }printf("NULL\n");
}
struct node* createnode(int data){
    struct node* temp=malloc(sizeof(struct node));
    temp->next=NULL;
    temp->data=data;
    return temp;
}
struct node* insertatend(struct node*head,int data){
    struct node* temp=(struct node*)malloc(sizeof(struct node));
    temp->data=data;
    struct node* p=head;
    while(p->next!=NULL){
        p=p->next;
    }
    p->next=temp;
    temp->next=NULL;
    return head;
} 
int main() {
    struct node* head = createnode(1);
    head=insertatend(head,2);
    head=insertatend(head,3);
    head=insertatend(head,4);
    head= insertatend(head,5);
    display(head);
    head=reverseBetween(head,2,5);
    display(head);
    if (isPalindrome(head)) {
        printf("Linked list is a palindrome.\n");
    } else {
        printf("Linked list is not a palindrome.\n");
    }
    return 0;
}
