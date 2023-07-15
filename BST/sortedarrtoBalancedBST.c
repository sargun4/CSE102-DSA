#include<stdio.h>
#include<stdlib.h>
struct node{
	int data;
	struct node* left;
	struct node* right;
};
struct node* newNode(int data);
/* A function that construts Balanced Binary Search Tree from a sorted array */
struct node* sortedArrayToBST(int arr[], int start, int end){
	if (start > end)
	return NULL;
	/* Get the middle element and make it root */
	int mid = (start + end)/2;
	struct node *root = newNode(arr[mid]);
	/* Recursively construct the left subtree and make it
	left child of root */
	root->left = sortedArrayToBST(arr, start, mid-1);
	/* Recursively construct the right subtree and make it
	right child of root */
	root->right = sortedArrayToBST(arr, mid+1, end);
	return root;
}
/* Helper function that allocates a new node with the
given data and NULL left and right pointers. */
struct node* newNode(int data){
	struct node* node = (struct node*)malloc(sizeof(struct node));
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	return node;
}
void preOrder(struct node* node){
	if (node == NULL)
		return;
	printf("%d ", node->data);
	preOrder(node->left);
	preOrder(node->right);
}
int main(){
	int arr[] = {1, 2, 3, 4, 5, 6, 7};
	int n = sizeof(arr)/sizeof(arr[0]);
	/* Convert List to BST */
	struct node *root = sortedArrayToBST(arr, 0, n-1);
	printf("n PreOrder Traversal of constructed BST ");
	preOrder(root);

	return 0;
}
