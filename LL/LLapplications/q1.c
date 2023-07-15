// Create a linked list  in C
// with each node contain names of student and their
// CGPA.
// 2 Given the above list, find the name of the student having the
// highest CGPA.
// 3 Given a list, create two lists with alternate elements of first list.
// 4 Append a list at end of another list.
// 5 Check if two lists are identical.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    char name[50];
    float cgpa;
    struct student *next;
};

typedef struct student student;

student* createNode(char name[], float cgpa) {
    student* newNode = (student*) malloc(sizeof(student));
    strcpy(newNode->name, name);
    newNode->cgpa = cgpa;
    newNode->next = NULL;
    return newNode;
}

student* insertNode(student* head, char name[], float cgpa) {
    student* newNode = createNode(name, cgpa);
    if (head == NULL) {
        head = newNode;
    } else {
        student* curr = head;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = newNode;
    }
    return head;
}

void printList(student* head) {
    student* curr = head;
    while (curr != NULL) {
        printf("%s (%.2f) -> ", curr->name, curr->cgpa);
        curr = curr->next;
    }printf("NULL\n");
}

char* findMaxCGPA(student* head) {
    if (head == NULL) {
        return NULL;
    }
    float maxCGPA = head->cgpa;
    char* maxName = head->name;
    student* curr = head->next;
    while (curr != NULL) {
        if (curr->cgpa > maxCGPA) {
            maxCGPA = curr->cgpa;
            maxName = curr->name;
        }
        curr = curr->next;
    }
    return maxName;
}

void splitList(student* head, student** list1, student** list2) {
    student* curr1 = NULL;
    student* curr2 = NULL;
    student* curr = head;
    int i = 1;
    while (curr != NULL) {
        if (i % 2 == 1) {
            if (curr1 == NULL) {
                curr1 = createNode(curr->name, curr->cgpa);
                *list1 = curr1;
            } else {
                curr1->next = createNode(curr->name, curr->cgpa);
                curr1 = curr1->next;
            }
        } else {
            if (curr2 == NULL) {
                curr2 = createNode(curr->name, curr->cgpa);
                *list2 = curr2;
            } else {
                curr2->next = createNode(curr->name, curr->cgpa);
                curr2 = curr2->next;
            }
        }
        curr = curr->next;
        i++;
    }
}

student* appendList(student* list1, student* list2) {
    if (list1 == NULL) {
        return list2;
    }
    student* curr = list1;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = list2;
    return list1;
}

int checkIdentical(student* list1, student* list2) {
    while (list1 != NULL && list2 != NULL) {
        if (strcmp(list1->name, list2->name) != 0 || list1->cgpa != list2->cgpa) {
            return 0;
        }
        list1 = list1->next;
        list2 = list2->next;
    }
    return list1 == NULL && list2 == NULL;
}
int main() {
    // Create a linked list
    student* head = NULL;
    head = insertNode(head, "Alice", 3.8);
    head = insertNode(head, "Bob", 3.6);
    head = insertNode(head, "Charlie", 4.0);
    head = insertNode(head, "David", 3.9);

    // Print the list
    printf("Linked List:\n");
    printList(head);

    // Find the name of the student with the highest CGPA
    char* maxName = findMaxCGPA(head);
    printf("Student with highest CGPA: %s\n", maxName);

    // Split the list into two alternate lists
    student* list1 = NULL;
    student* list2 = NULL;
    splitList(head, &list1, &list2);
    printf("List 1:\n");
    printList(list1);
    printf("List 2:\n");
    printList(list2);

    // Append a list to the end of another list
    student* newList = NULL;
    newList = insertNode(newList, "Eve", 4.0);
    newList = insertNode(newList, "Frank", 3.7);
    printf("New List:\n");
    printList(newList);
    head = appendList(head, newList);
    printf("Merged List:\n");
    printList(head);

    // Check if two lists are identical
    student* identicalList = NULL;
    identicalList = insertNode(identicalList, "Alice", 3.8);
    identicalList = insertNode(identicalList, "Bob", 3.6);
    identicalList = insertNode(identicalList, "Charlie", 4.0);
    identicalList = insertNode(identicalList, "David", 3.9);
    printf("Identical List:\n");
    printList(identicalList);
    printf("Lists are identical: %d\n", checkIdentical(head, identicalList));

    return 0;
}
