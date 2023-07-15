#include <stdio.h>
#include <stdlib.h>
struct cllnode{
    int data;
    struct node* next;
};
int len(struct cllnode *head){
    struct cllnode *curr=head;
    int ctr=0;
    if(head==NULL) return 0;
    do{
        curr=curr->next;
        ctr++;
    }while(curr!=head);
    return ctr;
}
void printcll(struct cllnode* head){
    struct cllnode* curr=head;
    if(head==NULL) return;
    do{
        printf("%d",curr->data);
        curr=curr->next;
    }while(curr!=head);
}