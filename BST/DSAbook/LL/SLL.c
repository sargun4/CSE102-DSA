#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
struct node {
    int data;
    struct node *next;
};
struct node* allocate_node(int data) {
    struct node *n = (struct node*)malloc(sizeof(struct node));
    assert(n != NULL);
    n->data = data;
    n->next = NULL;
    return n;
}
struct node* insert_front(struct node *head, struct node *n) {
    n->next = head;
    return n; 
}
void print_list(struct node *head) {
    struct node *temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}
void insert_rear(struct node *head, struct node *n) {
    assert(head != NULL);
    struct node *tmp = head;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = n;
}
void insertatpos(struct node* head,struct node*n,int idx){
    struct node* temp=head;
    // temp->data=data;
    int i=0;
    while (i<idx && temp->next!=NULL){
        temp=temp->next;
        i++;
    }if(temp!=NULL){
        n->next=temp->next;
        temp->next=n;
    }   
}
struct node* search(struct node*head,int val){
    struct node*temp=head;
    while(temp!=NULL){
        if(temp->data=val){
            return temp;
        }temp=temp->next;
    }return NULL;
}
struct node* recsearch(struct node*head,int val){
    if(head==NULL) return NULL;
    if(head->data==val) return head;
    return recsearch(head->next,val);
}
struct node *delfront(struct node**head){
    struct node* temp=*head;
    *head=temp->next;
    return temp;
}
struct node* delend(struct node**head){
    struct node* temp=*head;
    if(temp->next==NULL){
        *head=NULL;
        return temp;
    }
    struct node*prev=temp;
    temp=temp->next;
    while (temp->next!=NULL){
        prev=temp;
        temp=temp->next;
    }
    prev->next=NULL;
    return temp;
}
struct node *rev(struct node*head){
    struct node*prev,*next=NULL;
    struct node*curr=head;
    while(curr!=NULL){
        next=curr->next;
        curr->next=prev;
        prev=curr;
        curr=next;
    }return prev;
}
struct node* rev_rec(struct node*head){
    assert(head!=NULL);
    struct node*next=head->next;
    if(next==NULL) return head;
    struct node* headsublist=rev_rec(next);
    next->next=head;
    head->next=NULL;
    return headsublist;
}
struct node *del(struct node **head,struct node*n){
    struct node* temp=*head;
    if(temp==n){
        *head=temp->next;
        return temp;
    }
    if(temp->next=NULL) return NULL;
    struct node*prev=temp;
    temp=temp->next;
    while(temp->next!=NULL && temp!=n){
        prev=temp;
        temp=temp->next;
    }
    if(temp==n){
        prev->next=temp->next;
        return temp;
    }
    return NULL;
}
int main() {
    struct node *head = allocate_node(1);
    struct node *n;
    int i,sum=0;
    for (i = 2; i <= 5; i++) {
        n = allocate_node(i);
        head = insert_front(head, n);}
    print_list(head);

    for (i = 2; i <= 5; i++) {
        n = allocate_node(i);
        insert_rear(head, n); }
    print_list(head);
    while (head != NULL) {
        sum += head->data;
        head = head->next;
    }
    
    printf("sum of all nodes is : %d\n", sum);
    return 0;
}
