#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};

void display(struct node* head) {
    struct node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
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


void insertatstart(struct node** head,int data){
    struct node *temp = createnode(data);
    temp->next = *head;
    *head = temp;
    // temp->next=createnode(data);
}
void insertatidx(struct node* head,int data,int idx){
    struct node *nxtnode, *temp = head;
    int i=0;
    while (i<idx){
        if (temp->next == NULL){
            insertatend(head, data);
            return;
        }       
        temp = temp->next;
        i++;
    }
    nxtnode = temp->next;
    temp->next=createnode(data);
    temp->next->next = nxtnode;
}
void deleteAtIndex(struct node** head, int idx) {
    struct node* temp = *head;
    struct node* prev = NULL;
    // Traverse the list to the node at the index
    for (int i = 0; i < idx && temp != NULL; i++) {
        prev = temp;
        temp = temp->next;
    } 
    // If the index is out of bounds, do nothing
    if (temp == NULL) {
        return;
    }
    // Update the prev node's next pointer to skip the current node
    if (prev != NULL) {
        prev->next = temp->next;
    } else {
        *head = temp->next;
    }
    // Free the memory allocated to the deleted node
    free(temp);
}
int main(){
    struct node head;
    struct node *ptr;
    ptr = createnode(0);
    ptr->next = createnode(1);
    ptr->next->next = createnode(2);
    ptr->next->next->next = createnode(3);
    insertatend(ptr,4);
    insertatstart(&ptr,11);
    deleteAtIndex(&ptr,1);
    insertatidx(ptr,7,55);
    display(ptr);
    return 0;
}