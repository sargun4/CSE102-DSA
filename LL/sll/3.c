#include<stdio.h>
#include<stdlib.h>

struct node {
      int data;
      struct node *next;
};
struct node* reverseBetween(struct node* head, int left, int right) {
    if (head == NULL || left == right) {
        return head;
    }    
    struct node* dummy = (struct node*)malloc(sizeof(struct node));    dummy->next = head;
    struct node* prev = dummy;
    struct node* curr = head;
    // Move to the left position
    for (int i = 1; i < left; i++) {
        prev = prev->next;
        curr = curr->next;
    }
    // Reverse the sublist from left to right
    for (int i = 0; i < right - left; i++) {
        struct node* temp = curr->next;
        curr->next = temp->next;
        temp->next = prev->next;
        prev->next = temp;
    }
    head = dummy->next;
    free(dummy);
    return head;
}
// struct node* reverseBetween(struct node* head, int left, int right){
//     struct node* l=head; int lctr=0;
//     struct node* r=head; int rctr=0;
//     while(lctr<left){
//         l=l->next;
//         lctr++;
//     }
//     while(rctr<right){
//         r=r->next;
//         rctr++;
//     }
//     struct node* prev=NULL,*next=NULL,*curr=l;
//     while(curr!=r->next){
//         next=curr->next;
//         curr->next=prev;
//         prev=curr;
//         curr=next;
//     }
//     head->next=prev;
//     l->next=r->next;
//     return head;
// }
void display(struct node* temp){
    while(temp!=NULL){
        printf("%d -> ",temp->data);
        temp=temp->next;
    }printf("NULL\n");
}
struct node* insertAtEnd(struct node* head, int data) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = data;
    temp->next = NULL;

    if (head == NULL) {
        return temp;
    }

    struct node* curr = head;
    while (curr->next != NULL) {
        curr = curr->next;
    }

    curr->next = temp;
    return head;
}

int main() {
    struct node* head = NULL;
    for (int i = 0; i < 5; i++) {
        head = insertAtEnd(head, i + 1);
    }
    display(head);

    head = reverseBetween(head, 2, 4);
    display(head);

    return 0;
}