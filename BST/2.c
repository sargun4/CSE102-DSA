#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
struct node {
      int val;
      struct node *left;
     struct node *right;
};
#define MAX_SIZE 1000
//iterative preorder
int* preorderTraversal(struct node* root, int* returnSize) {
    if (root == NULL) {
        *returnSize = 0;
        return NULL;
    }
    
    int* result = (int*)malloc(MAX_SIZE * sizeof(int));
    *returnSize = 0;
    
    struct node* stack[MAX_SIZE];
    int top = -1;
    
    stack[++top] = root;
    
    while (top >= 0) {
        struct node* node = stack[top--];
        result[(*returnSize)++] = node->val;
        
        if (node->right) {
            stack[++top] = node->right;
        }
        if (node->left) {
            stack[++top] = node->left;
        }
    }
    
    return result;
}

bool isLeaf(struct node *node){
  if (node == NULL)
    return false;
  if (node->left == NULL && node->right == NULL)
    return true;
  return false;
}
 
// This function returns sum of all left leaves in a given
// binary tree
int leftLeavesSum(struct node *root){
  // Initialize result
  int res = 0;
 
  // Update result if root is not NULL
  if (root != NULL)
  {
    // If left of root is NULL, then add key of
    // left child
    if (isLeaf(root->left))
      res += root->left->val;
    else // Else recur for left child of root
      res += leftLeavesSum(root->left);
 
    // Recur for right child of root and update res
    res += leftLeavesSum(root->right);
  }
 
  // return result
  return res;
}