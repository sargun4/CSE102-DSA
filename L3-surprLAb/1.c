#include <stdio.h>
#include <stdlib.h>
#include<string.h>
struct node {
    int data;
    struct node* next;
} node;

struct node* createNode(int data) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

struct node* insert(struct node* head, int data) {
    struct node* newNode = createNode(data);
    if (head == NULL) {
        head = newNode;
    } else {
        struct node* curr = head;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = newNode;
    }
    return head;
}

struct node* delete(struct node* head, int k) {
    if (k == 1) {
        struct node* temp = head;
        head = head->next;
        free(temp);
    } else {
        struct node* curr = head;
        int i = 1;
        while (i < k - 1) {
            curr = curr->next;
            i++;
        }
        struct node* temp = curr->next;
        curr->next = temp->next;
        free(temp);
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

struct node* rev(struct node* head) {
    struct node* curr = head;
    struct node* prev = NULL;
    struct node* next = NULL;
    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
    return head;
}

int kthNode(struct node* head, int k) {
    int len = length(head);
    if (k > len) {
        return -1;
    } else {
        struct node* curr = head;
        int i = 1;
        while (i < k) {
            curr = curr->next;
            i++;
        }
        return curr->data;
    }
}

void printList(struct node* head) {
    if (head == NULL) {
        printf("EMPTY");
    } else {
        struct node* curr = head;
        while (curr != NULL) {
            printf("%d ", curr->data);
            curr = curr->next;
        }
    }
    printf("\n");
}
int main() {
    struct node* head = NULL;
    int n, q, data, k;
    char query[10];
    scanf("%d%d", &n, &q);
    for (int i = 0; i < n; i++) {
        scanf("%d", &data);
        head = insert(head, data);
    }
    while (q--) {
        scanf("%s", query);
        if (strcmp(query, "Reverse") == 0) {
            head = rev(head);
        } else if (strcmp(query, "Print") == 0) {
            printList(head);
        } else if (strcmp(query, "Length") == 0) {
            printf("%d\n", length(head));
        } else if (strcmp(query, "KthNode") == 0) {
            scanf("%d", &k);
            printf("%d\n", kthNode(head, k));
        } else if (strcmp(query, "Delete") == 0) {
            scanf("%d", &k);
            if (k > length(head)) {
                printf("-1\n");
            } else {
                head = delete(head,k);
            }
        }
        }
    }