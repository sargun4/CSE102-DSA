#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* prev;
    struct node* next;
};

struct node* create_node(int data) {
    struct node* new_node = malloc(sizeof(struct node));
    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}

void display(struct node* head) {
    struct node* temp = head;
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void insert_at_head(struct node** head_ref, int data) {
    struct node* new_node = create_node(data);
    if (*head_ref == NULL) {
        *head_ref = new_node;
    } else {
        (*head_ref)->prev = new_node;
        new_node->next = *head_ref;
        *head_ref = new_node;
    }
}

void insert_at_tail(struct node** head_ref, int data) {
    struct node* new_node = create_node(data);
    if (*head_ref == NULL) {
        *head_ref = new_node;
    } else {
        struct node* temp = *head_ref;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
        new_node->prev = temp;
    }
}

void delete_at_head(struct node** head_ref) {
    if (*head_ref == NULL) {
        return;
    }
    struct node* temp = *head_ref;
    *head_ref = temp->next;
    if (*head_ref != NULL) {
        (*head_ref)->prev = NULL;
    }
    free(temp);
}

void delete_at_tail(struct node** head_ref) {
    if (*head_ref == NULL) {
        return;
    }
    struct node* temp = *head_ref;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    if (temp->prev != NULL) {
        temp->prev->next = NULL;
    } else {
        *head_ref = NULL;
    }
    free(temp);
}

// struct node* insert_at_pos(struct node* head, int data, int pos) {
//     struct node* new_node = malloc(sizeof(struct node));
//     new_node->data = data;
//     new_node->prev = NULL;
//     new_node->next = NULL;

//     if (pos == 1) {
//         new_node->next = head;
//         head->prev = new_node;
//         head = new_node;
//     } else {
//         struct node* current = head;
//         for (int i = 1; i < pos - 1; i++) {
//             current = current->next;
//             if (current == NULL) {
//                 printf("Invalid position.\n");
//                 return head;
//             }
//         }
//         new_node->prev = current;
//         new_node->next = current->next;
//         if (current->next != NULL) {
//             current->next->prev = new_node;
//         }
//         current->next = new_node;
//     }

//     return head;
// }
struct node* delete_at_pos(struct node* head, int pos) {
    if (head == NULL) {
        printf("List is empty.\n");
        return head;
    }

    if (pos == 1) {
        struct node* temp = head;
        head = head->next;
        if (head != NULL) {
            head->prev = NULL;
        }
        free(temp);
    } else {
        struct node* current = head;
        for (int i = 1; i < pos; i++) {
            current = current->next;
            if (current == NULL) {
                printf("Invalid position.\n");
                return head;
            }
        }
        current->prev->next = current->next;
        if (current->next != NULL) {
            current->next->prev = current->prev;
        }
        free(current);
    }

    return head;
}


void insert_at_pos(struct node** head_ref, int data, int pos) {
    if (pos < 1) {
        printf("Invalid position.\n");
        return;
    }
    struct node* new_node = create_node(data);
    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }
    struct node* current = *head_ref;
    int i = 1;
    while (i < pos - 1 && current->next != NULL) {
        current = current->next;
        i++;
    }
    if (i < pos - 1) {
        printf("Position out of range.\n");
        return;
    }
    new_node->prev = current;
    new_node->next = current->next;
    if (current->next != NULL) {
        current->next->prev = new_node;
    }
    current->next = new_node;
}
void sort(struct node** head_ref) {
    struct node* i, *j;
    int temp;
    // bubble sort LL elmnts
    for (i = *head_ref; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->data > j->data) {
                temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}
struct node* reverse_k_nodes(struct node* head, int k) {
    struct node* current = head;
    struct node* next = NULL;
    struct node* prev = NULL;
    int count = 0;
    while (current != NULL && count < k) {
        next = current->next;
        current->next = prev;
        current->prev = next;
        prev = current;
        current = next;
        count++;
    }
    if (next != NULL) {
        head->next = reverse_k_nodes(next, k);
        head->next->prev = head;
    }
    return prev;
}
void reverse_dll(struct node** head_ref) {
    struct node* temp = NULL;
    struct node* current = *head_ref;
    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    if (temp != NULL) {
        *head_ref = temp->prev;
    }
}

int main() {
    struct node* head = NULL;

    insert_at_head(&head, 1);
    insert_at_head(&head, 2);
    insert_at_head(&head, 3);
    insert_at_head(&head, 4);
    display(head);

    insert_at_tail(&head, 5);
    insert_at_tail(&head, 6);
    insert_at_tail(&head, 7);
    display(head);

    delete_at_head(&head);
    delete_at_tail(&head);
    display(head);
    insert_at_pos(&head, 8, 1);
    display(head);
    sort(&head);
    display(head);
    head = reverse_k_nodes(head, 3);

    reverse_dll(&head);
    display(head);
    return 0;
}