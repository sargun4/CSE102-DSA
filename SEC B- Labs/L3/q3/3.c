#include <stdio.h>
#include <stdlib.h>
#include<string.h>

struct node {
    int data;
    struct node *next;
};

struct node* insertatend(struct node* head, int data){
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

int length(struct node* head) {
    int ctr = 0;
    struct node* curr = head;
    while (curr != NULL) {
        ctr++;
        curr = curr->next;
    }
    return ctr;
}

int kthNode(struct node* head, int k) {
    int len = length(head);
    if (k > len) {
        return -1;
    } else {
        struct node* curr = head;
        int i = 0;
        while (i<k-1) {
            curr = curr->next;
            i++;
        }
        return curr->data;
    }
}

struct node* del(struct node* head, int k) {
    if (head == NULL || k <= 0) {
        return head;
    }
    if (k == 1){
        struct node* temp = head;
        head = head->next;
        free(temp);
        return head;
    }
    struct node* curr = head;
    struct node* prev = NULL;
    int count = 1;
    while (curr != NULL && count != k) {
        prev = curr;
        curr = curr->next;
        count++;
    }
    if (curr != NULL) {
        prev->next = curr->next;
        free(curr);
    }
    return head;
}

void add_k_x(struct node *head,int k,int x){
    int len = length(head);
    if(k > len) {
        printf("-1\n");
        return;
    }
    if(k==1){
        head->data+=x;
    }else{
        struct node* temp=head;
        int i=1;
        while(i<k){
            temp=temp->next;
            i++;
        }
        temp->data+=x;
    }
}

void sub_k_x(struct node *head,int k,int x){
    int len = length(head);
    if(k > len) {
        printf("-1\n");
        return;
    }
    if(k==1){
        head->data-=x;
    }else{
        struct node* temp=head;
        int i=1;
        while(i<k){
            temp=temp->next;
            i++;
        }
        temp->data-=x;
    }
}
void xorK(struct node* head,int k){
    int len = length(head);
    if(k > len) {
        printf("-1\n");
        return;
    }
    struct node* temp=head;
    for(int i=0;i<len-k;i++){
        temp=temp->next;
    }
    int xor=0;
    while (temp!=NULL){
        xor^=temp->data;
        temp=temp->next;
    }
    printf("%d\n", xor);
}
int main() {
    struct node* head = NULL;
    int n, q, data, k, x;
    char query[15];
    scanf("%d%d", &n, &q);
    for (int i = 0; i < n; i++) {
        scanf("%d", &data);
        head=insertatend(head, data);
    }
    // display(head);
    while (q--) {
        scanf("%s", query);
        if (strcmp(query, "KthNode") == 0) {
            scanf("%d", &k);
            printf("%d\n", kthNode(head, k));
        } else if (strcmp(query, "Delete") == 0) {
            scanf("%d", &k);
            if (k > length(head)) {
                printf("-1\n");
            } else {
                del(head, k);
            }
        } else if (strcmp(query, "Add") == 0) {
            scanf("%d %d", &k, &x);
            if (k > length(head)) {
                printf("-1\n");
            } else {
                add_k_x(head, k, x);
            }
        } else if (strcmp(query, "Subtract") == 0) {
            scanf("%d %d", &k, &x);
            if (k > length(head)) {
                printf("-1\n");
            } else {
                sub_k_x(head, k, x);
            }
        } else if (strcmp(query, "Xor") == 0) {
            scanf("%d", &k);
            if (k > length(head)) {
                printf("-1\n");
            } else {
                xorK(head, k);
            }
        }
        // display(head);
    }
    return 0;
}
