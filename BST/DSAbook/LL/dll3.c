#include <stdio.h>
#include <stdlib.h>
struct node {
    int data;
    struct node* next,*prev;
};

void insert(struct node** head,int pos){
    int k=1;
    struct node* temp,*newnode;
    newnode=malloc(sizeof(struct node));
    if(!newnode){
        printf("Memory error");
        return;
    }
    newnode->data=data;
    if(pos==1){
        newnode->next=*head;
        newnode->prev=NULL;
        if(*head){
            *head->prev-newnode;
        }
        *head=newnode;
        return;
    }
    temp=*head;
    while(k<pos-1 && temp->next!=NULL){
        temp=temp->next;
        k++;
    }
    if(k!=pos) printf("pos doesnt exist\n");
    newnode->next=temp->next;
    newnode->prev=temp;
    if(temp->next){
        temp->next->prev=newnode;
    }
    temp->next-=newnode;
    return;
}
void delete(struct node** head,int pos){
    struct node* temp,*temp2;
    struct node* temp=*head;
    int k=1;
    if(*head==include){
        printf("List is empty");
        return;
    }
    if(pos==1) *head=*head->next;
    if(*head!=NULL){
        *head->prev=NULL;
        free(temp);
        return;
    }
    while(k<pos && temp->next!=NULL){
        temp=temp->next;
        k++;
    }if(k!=pos-1){
        printf("pos doesnt exist\n");
    }
    temp2=temp->prev;
    temp2->next=temp->next;
    if(temp->next){
        temp->next->prev=temp2;
    }
    free(temp);
    return;
}
int main(){
    
    return 0;
}
// #include <stdio.h>
// #include <stdlib.h>
// struct node {
//     int data;
//     struct node* next;
// };
// struct node* rev(struct node**head) {
//     struct node* current = *head;
//     struct node* next = NULL;
//     struct node* prev = NULL;
//     while (current != NULL ) {
//         next = current->next;
//         current->next = prev;
//         prev = current;
//         current = next;
//     }
//     *head=prev;
// }
// struct node* revknodes(struct node* head, int k) {
//     struct node* current = head;
//     struct node* next = NULL;
//     struct node* prev = NULL;
//     int count = 0;
//     while (current != NULL && count < k) {
//         next = current->next;
//         current->next = prev;
//         prev = current;
//         current = next;
//         count++;
//     }
//     if (next != NULL) {
//         head->next = revknodes(next, k);
//     }
//     return prev;
// }

// void display(struct node* node) {
//     while (node != NULL) {
//         printf("%d -> ", node->data);
//         node = node->next;
//     }
//     printf("NULL\n");
// }
// struct node* createnode(int data) {
//     struct node* node = (struct node*)malloc(sizeof(struct node));
//     node->data = data;
//     node->next = NULL;
//     return node;
// }
// struct node* insertatbegg(struct node* head,int data){
//     struct node* temp=malloc(sizeof(struct node));
//     temp->next=head;
//     temp->data=data;
    
//     return temp;
// }
// struct node* insertatidx(struct node* head,int data,int idx){
//     struct node* temp=malloc(sizeof(struct node));
//     temp->data=data;
//     struct node* p=head;
//     int i=1;
//     if(idx==0){
//         insertatbegg(head,data);
//     }
//     while(i!=idx){
//         p=p->next;
//         i++;
//     }
//     temp->next=p->next;
//     p->next=temp;
//     return head;
// }
// int main() {
//     struct node* head = createnode(1);
//     head->next = createnode(2);
//     head->next->next = createnode(3);
//     head->next->next->next = createnode(4);
//     head->next->next->next->next = createnode(5);
    
//     printf("Original List: ");
//     display(head);
//     printf("rev List: ");

//     rev(&head);
//     display(head);
    
//     int k = 2; 
//     head = revknodes(head, k);
//     printf("Reversed List (in groups of %d): ", k);
//     display(head);
    
//     insertatidx(head,8,1);
//     display(head);
    
//     insertatbegg(head,9);
//     display(head);
//     return 0;
// }
