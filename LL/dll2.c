#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

struct Node* findMiddleNode(struct Node* head) {
    struct Node* slow = head;
    struct Node* fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

struct Node* getNodeAtPosition(struct Node* head, int position) {
    if (head == NULL || position < 0) {
        return NULL;
    }
    struct Node* current = head;
    int count = 0;
    while (current != NULL && count < position) {
        current = current->next;
        count++;
    }
    if (current == NULL) {
        return NULL;
    }
    return current;
}
void swapNodesData(struct Node* head, int pos1, int pos2) {
    struct Node* node1 = getNodeAtPosition(head, pos1);
    struct Node* node2 = getNodeAtPosition(head, pos2);

    int temp = node1->data;
    node1->data = node2->data;
    node2->data = temp;
}

void deleteEvenNodes(struct Node** headRef) {
    struct Node* current = *headRef;
    while (current != NULL) {
        if (current->data % 2 == 0) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            } else {
                *headRef = current->next;
            }

            if (current->next != NULL) {
                current->next->prev = current->prev;
            }

            struct Node* temp = current;
            current = current->next;
            free(temp);
        } else {
            current = current->next;
        }
    }
}
 
void rotateList(struct Node** headRef, int k) {
    if (*headRef == NULL || k == 0) {
        return;
    }
    struct Node* current = *headRef;
    int count = 1;
    while (count < k && current != NULL) {
        current = current->next;
        count++;
    }
    if (current == NULL) {
        return;
    }
    struct Node* kthNode = current;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = *headRef;
    (*headRef)->prev = current;
    *headRef = kthNode->next;
    (*headRef)->prev = NULL;
    kthNode->next = NULL;
}

struct Node* getLastNode(struct Node* head) {
    struct Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    return current;
}
bool isPalindrome(struct Node* head) {
    struct Node* front = head;
    struct Node* back = getLastNode(head);
    while (front != NULL && back != NULL) {
        if (front->data != back->data) {
            return false;
        }
        front = front->next;
        back = back->prev;
    }
    return true;
}


void removeValue(struct Node** headRef, int value) {
    struct Node* current = *headRef;
    while (current != NULL) {
        if (current->data == value) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            } else {
                *headRef = current->next;
            }

            if (current->next != NULL) {
                current->next->prev = current->prev;
            }

            struct Node* temp = current;
            current = current->next;
            free(temp);
        } else {
            current = current->next;
        }
    }
}
struct Node* getKthFromEnd(struct Node* head, int k) {
    struct Node* first = head;
    struct Node* second = head;

    while (k > 0 && first != NULL) {
        first = first->next;
        k--;
    }

    if (first == NULL) {
        return NULL;
    }

    while (first != NULL) {
        first = first->next;
        second = second->next;
    }

    return second;
}
void insertAtEnd(struct Node** headRef, int value) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = NULL;

    if (*headRef == NULL) {
        *headRef = newNode;
    } else {
        struct Node* current = *headRef;

        while (current->next != NULL) {
            current = current->next;
        }

        current->next = newNode;
        newNode->prev = current;
    }
}
void reverseList(struct Node** headRef) {
    struct Node* current = *headRef;
    struct Node* temp = NULL;

    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }

    if (temp != NULL) {
        *headRef = temp->prev;
    }
}
void splitList(struct Node* head, struct Node** firstHalfRef, struct Node** secondHalfRef) {
    struct Node* slow = head;
    struct Node* fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    if (fast == NULL) {
        // even number of nodes
        *firstHalfRef = head;
        *secondHalfRef = slow;
        slow->prev = NULL;
    } else {
        // odd number of nodes
        *firstHalfRef = head;
        *secondHalfRef = slow->next;
        slow->next->prev = NULL;
        slow->next = NULL;
    }
}
void deleteKthNode(struct Node** headRef, int k) {
    struct Node* current = *headRef;

    while (k > 1 && current != NULL) {
        current = current->next;
        k--;
    }

    if (current != NULL) {
        if (current->prev != NULL) {
            current->prev->next = current->next;
        } else {
            *headRef = current->next;
        }

        if (current->next != NULL) {
            current->next->prev = current->prev;
        }

        free(current);
    }
}
int getLength(struct Node* head) {
    int count = 0;
    struct Node* current = head;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    return count;
}
void removeDuplicates(struct Node* head) {
    struct Node* current = head;
    struct Node* temp = NULL;

    while (current != NULL) {
        temp = current->next;
        while (temp != NULL && temp->data == current->data) {
            temp = temp->next;
        }
        current->next = temp;
        if (temp != NULL) {
            temp->prev = current;
        }
        current = current->next;
    }
}
void sortList(struct Node** headRef) {
    struct Node *i, *j;
    int temp;

    for (i = *headRef; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->data > j->data) {
                temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}
int getSecondLargest(struct Node* head) {
    if (head == NULL || head->next == NULL) {
        printf("Life is too short\n");
        return -1;
    }

    int max = head->data;
    int secondMax = INT_MIN;
    struct Node* current = head;

    while (current != NULL) {
        if (current->data > max) {
            secondMax = max;
            max = current->data;
        } else if (current->data > secondMax && current->data != max) {
            secondMax = current->data;
        }
        current = current->next;
    }

    if (secondMax == INT_MIN) {
        printf("No second largest element found\n");
        return -1;
    }

    return secondMax;
}
void rotateList(struct Node** headRef, int k) {
    if (k == 0) {
        return;
    }

    struct Node* current = *headRef;
    int count = 1;

    while (count < k && current != NULL) {
        current = current->next;
        count++;
    }

    if (current == NULL) {
        return;
    }

    struct Node* kthNode = current;

    while (current->next != NULL) {
        current = current->next;
    }

    current->next = *headRef;
    (*headRef)->prev = current;
    *headRef = kthNode->next;
    (*headRef)->prev = NULL;
    kthNode->next = NULL;
}
