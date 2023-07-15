#include <stdio.h>
#include <stdlib.h>
#include<string.h>
struct node {
    int data;
    struct node *next;
};

void insert(struct node **head, int data) {
    struct node *temp = (struct node*) malloc(sizeof(struct node));
    temp->data = data;
    temp->next = *head;
    *head = temp;  }

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
    int len = 0;
    struct node* p =head;
    while (p != NULL) {
        len++;
        p = p->next;
    }
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
// int kthNode(struct node* head, int k) {
//     if (head == NULL) {
//         return -1;
//     }
//     int len = length(head);
//     if (k > len || k<1) {
//         return -1;
//     } else {
//         struct node* curr = head;
//         int i = 0;
//         while (i < k-1) {
//             curr = curr->next;
//             i++;
//         }
//         return curr->data;
//     }
// }

struct node* del(struct node **head, int k) {
    struct node* curr = *head;
    struct node* prev = NULL;
    
    int count = 1;
    if (*head == NULL) {
        return NULL;
    }

    if (k == 1){
        *head = curr->next;
        free(curr);
        return *head;
    }

    while (curr != NULL && count != k) {
        prev = curr;
        curr = curr->next;
        count++;
    }

    if (curr != NULL) {
        prev->next = curr->next;
        free(curr);
    }

    return *head;
}

// struct node* del(struct node* head, int key) {
//     struct node* curr = head;
//     struct node* prev = NULL;
//     if (curr != NULL && curr->data == key) {
//         head = curr->next;
//         free(curr);
//         return head;
//     }
//     while (curr != NULL && curr->data != key) {
//         prev = curr;
//         curr = curr->next;
//     }
//     if (curr != NULL) {
//         prev->next = curr->next;
//         free(curr);
//     }
//     if (curr == NULL && prev != NULL && prev->next != NULL && prev->next->data == key) {
//         struct node* temp = prev->next;
//         prev->next = NULL;
//         free(temp);
//     }

//     if (curr == NULL && prev == NULL && head != NULL && head->data == key) {
//         struct node* temp = head;
//         head = NULL;
//         free(temp);
//     }

//     return head;
// }

// void del(struct node **head, int k) {
//     int len = length(*head);
//     if(k > len) {
//         printf("-1\n");
//         return;
//     }
//     if (k == 1) {
//         struct node* temp = *head;
//         *head = (*head)->next;
//         free(temp);
//     } else {
//         struct node* curr = *head;
//         int i = 1;
//         while (i < k - 1) {
//             curr = curr->next;
//             i++;
//         }
//         struct node* temp = curr->next;
//         curr->next = temp->next;
//         free(temp);
//     }
// }

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
void display(struct node*head){
    if(head==NULL) return;
    while(head!=NULL){
        printf("%d ",head->data);
        head=head->next;
    }
}
int main() {
    struct node* head = NULL;
    int n, q, data, k, x;
    char query[15];
    scanf("%d %d", &n, &q);
    struct node *prev, *temp;
    for (int i = 0; i < n; i++) {
        scanf("%d", &data);
        temp = (struct node*)malloc(sizeof(struct node));
        temp->data = data;
        temp->next = NULL;


    if (head == NULL) {
        head = temp;
        prev = temp;
        temp->next;
        continue;
    }
    prev->next = temp;
    prev = temp;
    temp = temp->next;
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
                del(&head, k);
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
