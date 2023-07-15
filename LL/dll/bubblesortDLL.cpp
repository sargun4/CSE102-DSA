#include <iostream>
using namespace std;
struct Node {
	int data;
	Node* prev;
	Node* next;
};
void insertAtTheBegin(struct Node **start_ref, int data){
	struct Node *ptr1 = new Node;
	ptr1->data = data;
	ptr1->next = *start_ref;
	if (*start_ref != NULL)
	(*start_ref)->prev = ptr1;
	*start_ref = ptr1;
}
void printList(struct Node *start){
	struct Node *temp = start;
	cout << endl;
	while (temp!=NULL){
		cout << temp->data << " ";
		temp = temp->next;
	}
}
void bubbleSort(struct Node *start){
	int swapped, i;
	struct Node *ptr1;
	struct Node *lptr = NULL;
	/* Checking for empty list */
	if (start == NULL)
		return;
	do{
		swapped = 0;
		ptr1 = start;
		while (ptr1->next != lptr){
			if (ptr1->data > ptr1->next->data){
				swap(ptr1->data, ptr1->next->data);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
	while (swapped);
}
int main(){
	int arr[] = {12, 56, 2, 11, 1, 90};
	int list_size, i;
	/* start with empty linked list */
	struct Node *start = NULL;
	/* Create linked list from the array arr[].
	Created linked list will be 1->11->2->56->12 */
	for (i = 0; i< 6; i++)
		insertAtTheBegin(&start, arr[i]);
	/* print list before sorting */
	printf("\n Linked list before sorting ");
	printList(start);
	/* sort the linked list */
	bubbleSort(start);
	/* print list after sorting */
	printf("\n Linked list after sorting ");
	printList(start);
	return 0;
}
