#include <stdio.h>
#include <stdlib.h>
struct node {
	int data;
	struct node *left, *right;
};
struct node* createnode(int x){
	struct node* p = malloc(sizeof(struct node));
	p->data = x;
	p->left = NULL;
	p->right = NULL;
	return p;
}
struct node* insert(struct node* root, int x){
	if (root == NULL)
		return createnode(x);
	if (x < root->data)
		root->left = insert(root->left, x);
	else if (x > root->data)
		root->right = insert(root->right, x);
	return root;
}
int count = 0;
void kthSmallest(struct node* root, int k, int* count, int* result){
    if (root == NULL || *count >= k) {
        return;
    }
    kthSmallest(root->left, k, count, result);
    *count += 1;
    if (*count == k) {
        *result = root->data;
        return;
    }
    kthSmallest(root->right, k, count, result);
}
int findmin(struct node* root){
    if (root == NULL) {
        return -1; // assuming all values are non-negative
    }
    while (root->left != NULL) {
        root = root->left;
    }
    return root->data;
}
int findmax(struct node* root){
    if (root == NULL) {
        return -1; // assuming all values are non-negative
    }
    while (root->right != NULL) {
        root = root->right;
    }
    return root->data;
}
int isBST(struct node* root){
    if(root==NULL) return 1;
    if(root->left!=NULL && findmax(root->left)>root->data){
        return 0;
    }
    if(root->right!=NULL && findmin(root->right)<root->data){
        return 0;
    }
    if(!isBST(root->left) || !isBST(root->right)) return 0;
    return 1;
}
int main(){
    struct node* root = NULL;
    int keys[] = { 20, 8, 22, 4, 12, 10, 14 };
    int len = sizeof(keys) / sizeof(keys[0]);
    for (int i = 0; i < len; i++) {
        root = insert(root, keys[i]);
    }
    if (isBST(root)) {
        printf("The binary tree is a binary search tree.\n");
    }else {
        printf("The binary tree is not a binary search tree.\n");
    }
    int k = 3;
    int count = 0, result = -1;
    kthSmallest(root, k, &count, &result);
    if (result != -1) {
        printf("The %dth smallest node in the binary search tree is %d.\n", k, result);
    }
    else {
        printf("The binary search tree does not have %d nodes.\n", k);
    }
    return 0;
}
