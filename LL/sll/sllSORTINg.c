#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
struct Node {
    int data;
    struct Node* next;
};

void bubbleSort(struct Node* head) {
    if (head == NULL) return;

    int swapped = 1;
    while (swapped) {
        swapped = 0;
        struct Node* ptr1 = head;
        struct Node* ptr2 = head->next;

        while (ptr2 != NULL) {
            if (ptr1->data > ptr2->data) {
                int temp = ptr1->data;
                ptr1->data = ptr2->data;
                ptr2->data = temp;
                swapped = 1;
            }
            ptr1 = ptr2;
            ptr2 = ptr2->next;
        }
    }
}

// 2.insertion sort
void insertionSort(struct Node** head) {
    if (*head == NULL) return;

    struct Node* sorted = NULL;
    struct Node* current = *head;

    while (current != NULL) {
        struct Node* next = current->next;

        if (sorted == NULL || current->data < sorted->data) {
            current->next = sorted;
            sorted = current;
        } else {
            struct Node* temp = sorted;
            while (temp->next != NULL && current->data > temp->next->data) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    *head = sorted;
}


// 3.MERGESORT
void frontBackSplit(struct Node* source, struct Node** frontRef, struct Node** backRef) {
    struct Node* slow = source;
    struct Node* fast = source->next;

    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}
// The frontBackSplit function takes three parameters:
// source: A pointer to the head of the list that needs to be split.
// frontRef: A pointer to the head of the first half of the split list.
// backRef: A pointer to the head of the second half of the split list.
// The function uses two pointers, slow and fast, to split the list. 
// The slow pointer moves one node at a time, while the fast pointer moves two nodes at a time. 
// When the fast pointer reaches the end of the list, the slow pointer points to the middle of the list.
//  The function then sets the frontRef to the original list and the backRef to the second half of the list.
struct Node* sortedMerge(struct Node* a, struct Node* b) {
    struct Node* result = NULL;

    if (a == NULL)
        return b;
    else if (b == NULL)
        return a;

    if (a->data <= b->data) {
        result = a;
        result->next = sortedMerge(a->next, b);
    } else {
        result = b;
        result->next = sortedMerge(a, b->next);
    }

    return result;
}

void mergeSort(struct Node **headRef){
    struct Node *head = *headRef;
    struct Node *a;
    struct Node *b;
  
    if ((head == NULL) || (head->next == NULL))
    {
        return;
    }
  
    frontBackSplit(head, &a, &b);
  
    mergeSort(&a);
    mergeSort(&b);
  
    *headRef = sortedMerge(a, b);
}
// a: A pointer to the head of the first sorted list.
// b: A pointer to the head of the second sorted list.
// The function recursively compares the first elements of both lists and adds the smaller element to the result 
// list. The function then calls itself with the remaining elements of the list until one of the lists becomes empty.
//  Once one of the lists becomes empty, 
// the function simply appends the remaining elements of the other list to the result list.