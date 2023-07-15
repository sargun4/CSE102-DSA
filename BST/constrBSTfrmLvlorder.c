// construct a BST from its level order traversal
#include <stdio.h>
#include<stdlib.h>
struct Node {
	int data;
	struct Node *left, *right;
};
 
struct Node* getNode(int data){ 
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->data = data;
	newNode->left = newNode->right = NULL;
	return newNode;
}
struct Node* LevelOrder(struct Node* root, int data){
	if (root == NULL) {
		root = getNode(data);
		return root;
	}
	if (data <= root->data)
		root->left = LevelOrder(root->left, data);
	else
		root->right = LevelOrder(root->right, data);
	return root;
}
struct Node* constructBst(int arr[], int n){
	if (n == 0)
		return NULL;
	struct Node* root = NULL;
	for (int i = 0; i < n; i++)
		root = LevelOrder(root, arr[i]);
	return root;
}
void inorderTraversal(struct Node* root){
	if (!root)
		return;

	inorderTraversal(root->left);
	printf("%d -> ",root->data);
	inorderTraversal(root->right);
	
}

int main(){
	int arr[] = { 7, 4, 12, 3, 6, 8, 1, 5, 10 };
	int n = sizeof(arr) / sizeof(arr[0]);
	struct Node* root = constructBst(arr, n);

	inorderTraversal(root);
	printf("NULL");
	return 0;
}
