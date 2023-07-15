#include <stdio.h>
#include <stdlib.h>
struct node{
    int data;
    struct node* next;
};
void display(struct node* head){
    struct node* temp=head;
    while(temp!=NULL){
        printf("%d -> ",temp->data);
        temp=temp->next;
    }printf("NULL\n");
}
struct node* insertathead(struct node*head,int data){
    struct node* temp=(struct node*)malloc(sizeof(struct node));
    temp->next=head;
    temp->data=data;
    return temp;
}

struct node* insertAtEnd(struct node* head, int data) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = data;
    temp->next = NULL;

    if (head == NULL) {
        head = temp;
    } else {
        struct node* p = head;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = temp;
    }

    return head;
}


struct node* insertatnxtidx(struct node*head,int data,int idx){
    struct node* temp=(struct node*)malloc(sizeof(struct node));
    struct node* p=head;
    int i=0;
    while(i!=idx){
        p=p->next;
        i++;
    }
    temp->data=data;
    temp->next=p->next;
    p->next=temp;
    return head;
}
void deletenode(struct node* head,int val){
    struct node* p=head;
    struct node* prev=NULL;
    if(p!=NULL && p->data==val){
        head=p->next;
        free(p);
        return;
    }
    while(p!=NULL && p->data !=val){
        prev=p;
        p=p->next;
    }
    if(p==NULL) return;
    prev->next=p->next;
    free(p);
}

struct node* search(struct node* head,int val){
    while(head!=NULL && head->data!=val){
        head=head->next;
    }return head;
}
struct node* findmin(struct node* head){
    struct node* minnode=head;
    while(head!=NULL){
        if(head->data < minnode->data){
            minnode=head;
        }head=head->next;
    }return minnode;
}
struct node* findmax(struct node* head){
    struct node* maxnode=head;
    while(head!=NULL){
        if(head->data > maxnode->data){
            maxnode=head;
        }head=head->next;
    }return maxnode;
}
void reverseList(struct node** head) {
    struct node* prev = NULL;
    struct node* current = *head;
    struct node* next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}

struct node* findMiddle(struct node* head) {
    struct node* slow = head;
    struct node* fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}
int hasCycle(struct node* head) {
    struct node* slow = head;
    struct node* fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return 1;
        }
    }
    return 0;
}
void deleteFromBeginning(struct node** head) {
    struct node* delnode = *head;
    *head = (*head)->next;
    free(delnode);
}
void deleteFromPosition(struct node** head, int position) {
    if (*head == NULL) return;
    struct node* delnode = *head;
    if (position == 0) {
        *head = (*head)->next;
        free(delnode);
        return;
    }
    struct node* prev = NULL;
    int i = 0;
    while (delnode != NULL && i < position) {
        prev = delnode;
        delnode = delnode->next;
        i++;
    }
    if (delnode == NULL) return;
    prev->next = delnode->next;
    free(delnode);
}

struct node* findNthFromEnd(struct node* head, int n) {
    if (head == NULL) return NULL;
    struct node* p1 = head;
    struct node* p2 = head;
    for (int i = 0; i < n; i++) {
        if (p1 == NULL) return NULL;
        p1 = p1->next;
    }
    while (p1 != NULL) {
        p1 = p1->next;
        p2 = p2->next;
    }
    return p2;
}

void deleteList(struct node** head) {
    struct node* current = *head;
    struct node* next = NULL;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

void sortList(struct node** head) {
    struct node* current = *head;
    struct node* idx = NULL;
    int temp;
    if (current == NULL) return;
    while (current != NULL) {
        idx = current->next;
        while (idx != NULL) {
            if (current->data > idx->data) {
                temp = current->data; //swap curr and idx
                current->data = idx->data;
                idx->data = temp;
            }
            idx = idx->next;
        }
        current = current->next;
    }
}

int main(){
    struct node* head=(struct node *)malloc(sizeof(struct node));
    struct node* second=(struct node *)malloc(sizeof(struct node));
    struct node* third=(struct node *)malloc(sizeof(struct node));
    
    head->data=4;
    head->next=second;
    second->data=3;
    second->next=third;
    third->data=2;
    third->next=NULL;
    display(head);

    head=insertathead(head,56);
    display(head);
    head=insertatnxtidx(head,8,1);
    display(head);
    deletenode(head,3);
    display(head);
    
    printf("SOrted in ascending order:");
    sortList(&head);
    display(head);

    struct node* minNode = findmin(head);
    printf("Minimum node: %d\n", minNode->data);
    struct node* maxNode = findmax(head);
    printf("Maximum node: %d\n", maxNode->data);

    reverseList(&head);
    display(head);
    findMiddle(head);
    struct node* middle = findMiddle(head);
    printf("Middle node: %d\n", middle->data);
    int has_cycle = hasCycle(head);
    printf("Has cycle: %d\n", has_cycle);
    deleteFromBeginning(&head);
    display(head);
    deleteFromPosition(&head, 2);
    display(head);
    struct node* nth_from_end = findNthFromEnd(head, 2);
    printf("2nd node from the end: %d\n", nth_from_end->data);
    return 0;
}
