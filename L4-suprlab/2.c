// You are given a Binary Tree as input in level order traversal form. You have to check if the given binary tree is an AVL tree or not. If it is an AVL tree, print "YES", else print "NO".

// Note: there will be binary marking for this question - you will get marks only if ALL test cases pass.

// Input
// The first line consists of an integer 1≤n≤1000
//  indicating total number of nodes in the binary tree
// The next lines contains binary tree nodes in level order traversal form. −1
//  indicates NULL node / NO node (see example). Each node's value ranges from 1≤ni≤106
// Output
// Print either "YES" or "NO" depending on whether given tree is AVL or not.

// Example
// inputCopy
// 6
// 50 20 80 15 -1 60 -1 -1 19 -1 -1 -1 -1
// outputCopy
// NO
// Note
// The Binary Tree created using given test case is not an AVL tree because balance factor at node with value 20 is 2.
#include <stdio.h>
#include <stdlib.h>
struct node {
    int data;
    struct node* left;
    struct node* right;
};
struct node* createnode(int data) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}
int height(struct node* root) {
    if (root == NULL)
        return 0;
    int leftht = height(root->left);
    int rightht = height(root->right);
    return((leftht > rightht) ? leftht : rightht) +1;
}
int isAVL(struct node* root) {
    if (root == NULL)
        return 1;
    int leftht = height(root->left);
    int rightht = height(root->right);
    if (abs(leftht - rightht) > 1)
        return 0;
    return isAVL(root->left) && isAVL(root->right);
}
struct node* buildTree(int* arr, int n, int i) {
    if (i >= n || arr[i] == -1)
        return NULL;
    struct node* root = createnode(arr[i]);
    root->left = buildTree(arr, n, 2 * i + 1);
    root->right = buildTree(arr, n, 2 * i + 2);
    return root;
}

int main() {
    int n;
    scanf("%d", &n);

    int* arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    struct node* root = buildTree(arr, n, 0);

    if (isAVL(root))
        printf("YES\n");
    else
        printf("NO\n");

    return 0;
}
