// Program to remove duplicates in an unsorted ll
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef struct node {
	int data;
	struct node* next;
} node;
node* createnode(int data){
	node* temp = (node*)malloc(sizeof(node));
	temp->data = data;
	temp->next = NULL;
	return temp;
}
void removeDuplicates(node* start){
	node *ptr1, *ptr2, *dup;
	ptr1 = start;
	/* Pick elements one by one */
	while (ptr1 != NULL && ptr1->next != NULL) {
		ptr2 = ptr1;
		/* Compare the picked element with rest
		of the elements */
		while (ptr2->next != NULL) {
			/* If duplicate then delete it */
			if (ptr1->data == ptr2->next->data) {
				/* sequence of steps is important here */
				dup = ptr2->next;
				ptr2->next = ptr2->next->next;
				free(dup);
			}
			else /* This is tricky */
				ptr2 = ptr2->next;
		}
		ptr1 = ptr1->next;
	}
}
void printList(struct node* node){
	while (node != NULL) {
		printf("%d ", node->data);
		node = node->next;
	}
}
bool isPalindrome(struct node* head) {
        struct node *slow = head, *fast = head, *prev, *temp;
        while (fast && fast->next)
            slow = slow->next, fast = fast->next->next;
        prev = slow, slow = slow->next, prev->next = NULL;
        while (slow)
            temp = slow->next, slow->next = prev, prev = slow, slow = temp;
        fast = head, slow = prev;
        while (slow)
            if (fast->data != slow->data) return false;
            else fast = fast->next, slow = slow->next;
        return true;
    }
bool isPalindrome(struct node* head) {
	struct node *slow = head, *fast = head, *prev = NULL, *tmp;
	while(fast && fast -> next) // finding mid point
		fast = fast -> next -> next,
		tmp = slow -> next, slow -> next = prev, prev = slow, slow = tmp;        
	slow = (fast ? slow -> next : slow); // for odd length case as mentioned above
	while(slow) // check if linked lists starting at prev and slow are equal
		if(slow -> data != prev -> data) return false;
		else slow = slow -> next, prev = prev -> next;
	return true;
}
bool isPalindrome(struct node* head) {
        // Steps to follow:
        // 1_) Find the middle element
        struct node *slow = head, *fast = head;
        while(fast!=NULL && fast->next !=NULL){
            slow = slow->next;
            fast = fast->next->next;
        }
        // 2_) if the no of nodes are odd then move slow to one point
        if(fast != NULL && fast->next == NULL){
            slow = slow->next;
        }
        //3_) Reverse the end half
        struct node *prev = NULL;
        struct node *temp = NULL;
        while(slow != NULL && slow->next != NULL){
            temp = slow->next;
            slow->next = prev;
            prev = slow;
            slow = temp;
        }
        if(slow != NULL){
            slow->next = prev;
        }
        //4_) Compare the start half and end half if found any inequality then return false otherwise return true.
        fast = head;
        while(slow && fast){
            if(slow->data != fast->data){
                return false;
            }
            slow = slow->next;
            fast = fast->next;
        }
        return true;

    }
int main(){
	struct node* start = createnode(10);
	start->next = createnode(12);
	start->next->next = createnode(11);
	start->next->next->next = createnode(11);
	start->next->next->next->next = createnode(12);
	start->next->next->next->next->next = createnode(11);
	start->next->next->next->next->next->next = createnode(10);
	printf("Linked list before removing duplicates ");
	printList(start);
	removeDuplicates(start);
	printf("\nLinked list after removing duplicates ");
	printList(start);
	return 0;
}