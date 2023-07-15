#include <stdio.h>
#include <stdlib.h>
struct node{
    int data;
    struct node* next;
};
void display(struct node* temp){
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
struct node* insertatnxtidx(struct node*head,int data,int idx){
    struct node* temp=(struct node*)malloc(sizeof(struct node));
    struct node* p=head;
    int i=1;
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
struct node* del(struct node*head,int val){
    struct node *ptr1,*ptr2;
    ptr1=head;
    while (ptr1->next!=NULL){
        if(ptr1->data==val){
            ptr2=ptr1->next;
            ptr1->next=ptr2->next;
            free(ptr2);
            break;
        }
        ptr1=ptr1->next;
    }    
    return head;
}
struct node* delall(struct node*head){
    struct node*ptr=head;
    while(ptr!=NULL){
        ptr=ptr->next;
        free(head);
        head=ptr;
    }
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
            return 1; // LL has cycle if  slow=fast.
        }
    }
    return 0;
}

void deleteFromBeginning(struct node** head) {
    struct node* toDelete = *head;
    *head = (*head)->next;
    free(toDelete);
}

void deleteFromPosition(struct node** head, int position) {
    if (*head == NULL) return;
    struct node* toDelete = *head;
    if (position == 0) {
        *head = (*head)->next;
        free(toDelete);
        return;
    }
    struct node* prev = NULL;
    int i = 0;
    while (toDelete != NULL && i < position) {
        prev = toDelete;
        toDelete = toDelete->next;
        i++;
    }
    if (toDelete == NULL) return;
    prev->next = toDelete->next;
    free(toDelete);
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
    struct node* index = NULL;
    int temp;
    if (current == NULL) return;
    while (current != NULL) {
        index = current->next;
        while (index != NULL) {
            if (current->data > index->data) {
                temp = current->data;
                current->data = index->data;
                index->data = temp;
            }
            index = index->next;
        }
        current = current->next;
    }
}
struct node* revknodes(struct node* head, int k) {
    struct node* current = head;
    struct node* next = NULL;
    struct node* prev = NULL;
    int count = 0;
    while (current != NULL && count < k) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
        count++;
    }
    //  reverse next k nodes of the list recursively 
    if (next != NULL) {
        head->next = revknodes(next, k);
    }
    //  prev is the new head of the input LL 
    return prev;
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
    
    int k = 2; // reverse k nodes at a time
    head = revknodes(head, k);
    
    printf("\nReversed List (in groups of %d): ", k);
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
// int main() {
//     char str1[] = "D";
//     char str2[] = "C";
//     // char str3[] = "hello";
//     int result1 = strcmp(str1, str2); // returns a negative number
//     printf("strcmp(str1, str2) = %d\n", result1);
//     return 0;
// }
