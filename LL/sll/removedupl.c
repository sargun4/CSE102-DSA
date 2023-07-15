#include <stdio.h>
#include <stdlib.h>
struct Node {
	int data;
	struct Node* next;
};
//for sorted ll only
void removeDuplicates(struct Node* head){
	struct Node* current = head;
	struct Node* next_next;
    if (current == NULL)
		return;
	/* Traverse the list till last node */
	while (current->next != NULL) {
		/* Compare current node with next node */
		if (current->data == current->next->data) {
			/* The sequence of steps is important*/
			next_next = current->next->next;
			free(current->next);
			current->next = next_next;
		}
		else{ //only advance if no deletion
			current = current->next;
		}
	}
}
void push(struct Node** head_ref, int new_data){
	struct Node* new_node= (struct Node*)malloc(sizeof(struct Node));
	new_node->data = new_data;
	new_node->next = (*head_ref);
	(*head_ref) = new_node;
}
void printList(struct Node* node){
	while (node != NULL) {
		printf("%d ", node->data);
		node = node->next;
	}
}
int main(){
	struct Node* head = NULL;
	push(&head, 20);
	push(&head, 13);
	push(&head, 13);
	push(&head, 11);
	push(&head, 11);
	push(&head, 11);
	printf("\n Linked list before duplicate removal \n");
	printList(head);
    removeDuplicates(head);
	printf("\n Linked list after duplicate removal \n");
	printList(head);
	return 0;
}

// #2
// C program to remove duplicates from a sorted linked list
#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
	int data;
	struct Node* next;
} Node;
// Function to remove duplicates
Node* removeDuplicates2(Node* head){
	// Two references to head temp will iterate to the whole
	// Linked List prev will point towards the first
	// occurrence of every element
	Node *temp = head, *prev = head;
	// Traverse list till the last node
	while (temp != NULL) {
		// Compare values of both pointers
		if (temp->data != prev->data) {
			// if the value of prev is not equal to the
			// value of temp that means there are no more
			// occurre`nces of the prev data-> So we can set
			// the next of prev to the temp node->*/
			prev->next = temp;
			prev = temp;
		}
		// Set the temp to the next node
		temp = temp->next;
	}
	// This is the edge case if there are more than one
	// occurrences of the last element
	if (prev != temp)
		prev->next = NULL;
	return head;
}
void push(Node** head_ref, int new_data){
	/* allocate node */
	Node* new_node = (Node*)malloc(sizeof(Node));
	/* put in the data */
	new_node->data = new_data;
	/* link the old list of the new node */
	new_node->next = (*head_ref);
	/* move the head to point to the new node */
	(*head_ref) = new_node;
}
void printList(Node* head){
	Node* temp = head;
	while (temp != NULL) {
		printf("%d ", temp->data);
		temp = temp->next;
	}
	printf("\n");
}
int main(){
	Node* llist = NULL;
	push(&llist, 20);
	push(&llist, 13);
	push(&llist, 13);
	push(&llist, 11);
	push(&llist, 11);
	push(&llist, 11);
	printf("List before removal of duplicates\n");
	printList(llist);
	printf("List after removal of elements\n");
	llist = removeDuplicates2(llist);
	printList(llist);
}
