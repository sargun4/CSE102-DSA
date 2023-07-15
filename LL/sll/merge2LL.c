#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode* next;
};

struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode dummy;
    struct ListNode* tail = &dummy;

    while (l1 && l2) {
        if (l1->val <= l2->val) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }

    tail->next = l1 ? l1 : l2;
    return dummy.next;
}

int main() {
    struct ListNode* l1 = (struct ListNode*)malloc(sizeof(struct ListNode));
    l1->val = 1;
    l1->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    l1->next->val = 3;
    l1->next->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    l1->next->next->val = 5;
    l1->next->next->next = NULL;

    struct ListNode* l2 = (struct ListNode*)malloc(sizeof(struct ListNode));
    l2->val = 2;
    l2->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    l2->next->val = 4;
    l2->next->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    l2->next->next->val = 6;
    l2->next->next->next = NULL;

    struct ListNode* merged = mergeTwoLists(l1, l2);

    while (merged != NULL) {
        printf("%d ", merged->val);
        merged = merged->next;
    }
    return 0;
}
