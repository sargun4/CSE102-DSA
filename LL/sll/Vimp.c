#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
struct node {
    int data;
    struct node* next;
};
struct node* reverseList(struct node* head) {
    struct node* prev = NULL;
    struct node* curr = head;
    struct node* next = NULL;
    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}
void deleteNode(struct node* node) {
    struct node* next = node->next;
    node->data = next->data;
    node->next = next->next;
    free(next);
}
struct node* rotateRight(struct node* head, int k) {
    if (head == NULL || head->next == NULL) {
        return head;
    }
    int len = 1;
    struct node* tail = head;
    while (tail->next != NULL) {
        tail = tail->next;
        len++;
    }
    k %= len;    
    if (k == 0) {
        return head;
    }
    struct node* newTail = head;    
    for (int i = 0; i < len - k - 1; i++) {
        newTail = newTail->next;
    }
    struct node* newHead = newTail->next;
    newTail->next = NULL;
    tail->next = head;
    return newHead;
}
struct node* merge(struct node* l1, struct node* l2) {
    if (l1 == NULL) {
        return l2;
    }
    if (l2 == NULL) {
        return l1;
    }
    if (l1->data < l2->data) {
        l1->next = merge(l1->next, l2);
        return l1;
    } else {
        l2->next = merge(l1, l2->next);
        return l2;
    }
}
struct node* sortList(struct node* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }    
    struct node* slow = head;
    struct node* fast = head->next;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    struct node* mid = slow->next;
    slow->next = NULL;
    struct node* left = sortList(head);
    struct node* right = sortList(mid);    
    return merge(left, right);
}
int kthSmallest(struct node* head, int k) {
    int count = 0;
    struct node* curr = head;
    while (curr != NULL) {
        count++;
        curr = curr->next;
    }
    if (k > count) {
        return -1;
    }
    curr = head;
    for (int i = 0; i < count - k; i++) {
        curr = curr->next;
    }    
    return curr->data;
}
int kthLargest(struct node* head, int k) {
    int count = 0;
    struct node* curr = head;
    while (curr != NULL) {
        count++;
        curr = curr->next;
    }
    if (k > count) {
       return -1;
    }
    curr = head;
    for (int i = 0; i < count - k; i++) {
        curr = curr->next;
    }    
    return curr->data;
}
struct node* reverseKGroup(struct node* head, int k) {
    struct node* curr = head;
    int count = 0;
    while (curr != NULL && count != k) {
        curr = curr->next;
        count++;
    }
    if (count == k) {
        curr = reverseKGroup(curr, k);   
        while (count-- > 0) {
            struct node* temp = head->next;
            head->next = curr;
            curr = head;
            head = temp;
        }   
        head = curr;
    }
    return head;
}
void splitList(struct node* head, struct node** first, struct node** second) {
    struct node* slow = head;
    struct node* fast = head->next;
    
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    
    *first = head;
    *second = slow->next;
    slow->next = NULL;
}
struct node* mergeLists(struct node* l1, struct node* l2) {
    if (l1 == NULL) {
        return l2;
    }
    
    if (l2 == NULL) {
        return l1;
    }
    
    if (l1->data < l2->data) {
        l1->next = mergeLists(l1->next, l2);
        return l1;
    } else {
        l2->next = mergeLists(l1, l2->next);
        return l2;
    }
}
void multiplyList(struct node* head, int x) {
    struct node* curr = head;
    
    while (curr != NULL) {
        curr->data *= x;
        curr = curr->next;
    }
}
bool isPalindrome(struct node* head) {
    struct node* slow = head;
    struct node* fast = head;
    struct node* prev = NULL;
    struct node* temp;
    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        temp = slow->next;
        slow->next = prev;
        prev = slow;
        slow = temp;
    }
    if (fast != NULL) {
        slow = slow->next;
    }
    while (prev != NULL && slow != NULL) {
        if (prev->data != slow->data) {
            return false;
        }
        prev = prev->next;
        slow = slow->next;
    }
    return true;
}
struct node* removeNthFromEnd(struct node* head, int n) {
    struct node* slow = head;
    struct node* fast = head;
    for (int i = 0; i < n; i++) {
        fast = fast->next;
    }
    if (fast == NULL) {
        return head->next;
    }
    while (fast->next != NULL) {
        slow = slow->next;
        fast = fast->next;
    }
    slow->next = slow->next->next;
    return head;
}
//Remove all nodes with a given value from a singly linked list:
struct node* removeElements(struct node* head, int data) {
    struct node* curr = head;
    struct node* prev = NULL;
    
    while (curr != NULL) {
        if (curr->data == data) {
            if (prev == NULL) {
                head = curr->next;
            } else {
                prev->next = curr->next;
            }
        } else {
            prev = curr;
        }
        curr = curr->next;
    }
    return head;
}
struct node* reverseAltKNodes(struct node* head, int k) {
    struct node* curr = head;
    struct node* prev = NULL;
    struct node* next = NULL;
    int count = 0;
    while (curr != NULL && count < k) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
        count++;
    }
    if (head != NULL) {
        head->next = curr;
    }
    count = 0;
    while (count < k - 1 && curr != NULL) {
        curr = curr->next;
        count++;
    }    
    if (curr != NULL) {
        curr->next = reverseAltKNodes(curr->next, k);
    }
    return prev;
}

