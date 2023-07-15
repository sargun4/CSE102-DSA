#include <stdio.h>
#include <stdlib.h>
struct node {
    int val;
    struct node *left;
    struct node *right;
};
struct node* createnode(int val) {
    struct node* root = (struct node*) malloc(sizeof(struct node));
    root->val = val;
    root->left = NULL;
    root->right = NULL;
    return root;
}
struct node* insert(struct node* root, int val) {
    if (root == NULL) {
        return createnode(val);
    }
    if (val < root->val) {
        root->left = insert(root->left, val);
    } else {
        root->right = insert(root->right, val);
    }
    return root;
}
// Function to do inorder traversal of binary tree
void inorderTraversal(struct node* root, int* arr, int* i) {
    if (root == NULL) {
        return;
    }
    inorderTraversal(root->left, arr, i);
    arr[(*i)++] = root->val;
    inorderTraversal(root->right, arr, i);
}
struct node* convertToBST(struct node* root) {
    int n = 0;
    struct node* curr = root;
    while (curr != NULL) {
        if (curr->left == NULL) {
            n++;
            curr = curr->right;
        } else {
            // Find inorder predecessor
            struct node* pred = curr->left;
            while (pred->right != NULL && pred->right != curr) {
                pred = pred->right;
            }
            if (pred->right == NULL) {
                pred->right = curr;
                curr = curr->left;
            } else {
                pred->right = NULL;
                n++;
                curr = curr->right;
            }
        }
    }    
    // Store inorder traversal of binary tree in array
    int* arr = (int*) malloc(n * sizeof(int));
    int i = 0;
    inorderTraversal(root, arr, &i);
    // Convert array to BST
    struct node* newRoot = NULL;
    for (int j = 0; j < n; j++) {
        newRoot = insert(newRoot, arr[j]);
    }
    free(arr);
    
    return newRoot;
}
void inorder(struct node* root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    printf("%d ", root->val);
    inorder(root->right);
}
int main() {
    struct node* root = createnode(10);
    root->left = createnode(30);
    root->right = createnode(15);
    root->left->left = createnode(20);
    root->right->right = createnode(5);
    // Convert binary tree to BST
    struct node* newRoot = convertToBST(root);
    // Print inorder traversal of BST
    inorder(newRoot);  
    return 0;
}
