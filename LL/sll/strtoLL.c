#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct node {
    char data;
    struct node* next;
};
struct node* add_node(char data){
    struct node* newnode =(struct node*) malloc(sizeof(struct node));
    newnode->data = data;
    newnode->next = NULL;
    return newnode;
}
// Function to convert a string to a singly linked list
void string_to_SLL(char* text, struct node** head_ref){
    struct node* curr = *head_ref;
    if(curr == NULL) {
        *head_ref = add_node(text[0]);
        curr = *head_ref;
    }
    else{
        while(curr->next != NULL)
            curr = curr->next;
        curr->next = add_node(text[0]);
        curr = curr->next;
    }
    for (int i = 1; i < strlen(text); i++) {
        curr->next = add_node(text[i]);
        curr = curr->next;
    }
}
// Function to print the data present in all the nodes
void print_list(struct node* head){
    struct node* curr = head;
    while (curr != NULL) {
        printf("%c -> ", curr->data);
        curr = curr->next;
    }
    printf("NULL\n");
}
int main(){
    char text[] = "GEEKS";
    struct node* head = NULL;
    string_to_SLL(text, &head);
    print_list(head);
    return 0;
}
