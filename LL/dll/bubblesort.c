#include <stdio.h>
#include <stdlib.h>
struct node {
    int data;
    struct node *next;
};
struct node* createnode(int data){
    struct node* temp=malloc(sizeof(struct node));
    temp->data=data;
    temp->next=NULL;
    return temp;
}
void display(struct node* head){
    struct node* temp=head;
    while(temp!=NULL){
        printf("%d -> ",temp->data);
        temp=temp->next;
    }printf("NULL\n");
}
void bubblesort(struct node** start,int n){
    int i,j,temp;
    struct node* ptr1,*ptr2;
    int k=n;
    for(i=0;i<n-1;i++,k--){
        ptr1=*start;
        ptr2=ptr1->next;
        for(j=1;j<k;j++){
            if(ptr1->data > ptr2->data){
                temp=ptr1->data;
                ptr1->data=ptr2->data;
                ptr2->data=temp;
            }
            ptr1=ptr1->next;
            ptr2=ptr2->next;
        }
    }
}
int count(struct node* head){
    int c=0;
    struct node* temp=head;
    while(temp!=NULL){
        temp=temp->next;
        c++;
    }return c;
}
void deleteN(struct node** head, int position)
{
    struct node* temp= *head;
    struct node* prev= *head;
    for (int i = 0; i < position; i++) {
        if (i == 0 && position == 1) {
            *head = (*head)->next;
            free(temp);
        }
        else {
            if (i == position - 1 && temp) {
                prev->next = temp->next;
                free(temp);
            }
            else {
                prev = temp;
 
                // Position was greater than
                // number of nodes in the list
                if (prev == NULL)
                    break;
                temp = temp->next;
            }
        }
    }
}
// void remove(struct node**p,int data){
//     struct node*t,*prev=NULL;
//     t=*q;
// }
int main() {
    struct node* head=createnode(1);
    head->next=createnode(3);
    head->next->next=createnode(2);
    display(head);
    int x=count(head);
    bubblesort(&head,x);
    display(head);
    return 0;
}
