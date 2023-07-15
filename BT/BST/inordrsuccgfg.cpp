// C++ program to find predecessor and successor in a BST
#include <iostream>
using namespace std;
// BST Node
struct Node{
	int data;
	struct Node *left, *right;
};
// This function finds predecessor and successor of data in BST.
// It sets pre and suc as predecessor and successor respectively
void findPreSuc(Node* root, Node*& pre, Node*& suc, int data){
	// Base case
	if (root == NULL) return ;
	// If data is present at root
	if (root->data == data){
		// the maximum value in left subtree is predecessor
		if (root->left != NULL){
			Node* tmp = root->left;
			while (tmp->right)
				tmp = tmp->right;
			pre = tmp ;
		}
		// the minimum value in right subtree is successor
		if (root->right != NULL){
			Node* tmp = root->right ;
			while (tmp->left)
				tmp = tmp->left ;
			suc = tmp ;
		}
		return ;
	}
	// If data is smaller than root's data, go to left subtree
	if (root->data > data){
		suc = root ;
		findPreSuc(root->left, pre, suc, data) ;
	}
	else {// go to right subtree
		pre = root ;
		findPreSuc(root->right, pre, suc, data) ;
	}
}
Node *createnode(int data){
	Node *temp = new(Node);
	temp->data = data;
	temp->left = temp->right = NULL;
	return temp;
}
struct Node* insert(struct Node* node, int data){
	if (node == NULL) return createnode(data);
	if (data < node->data)
		node->left = insert(node->left, data);
	else
		node->right = insert(node->right, data);
	return node;
}
int main(){
	int data = 65; //Key to be searched in BST
	/*	   50
		  /	 \
		30	 70
		/ \ / \
	  20 40 60 80 */
	Node *root = NULL;
	root = insert(root, 50);
	insert(root, 30);
	insert(root, 20);
	insert(root, 40);
	insert(root, 70);
	insert(root, 60);
	insert(root, 80);
	Node* pre = NULL, *suc = NULL;
	findPreSuc(root, pre, suc, data);
	if (pre != NULL)
	cout << "Predecessor is " << pre->data << endl;
	else
	cout << "No Predecessor";
	if (suc != NULL)
	cout << "Successor is " << suc->data;
	else
	cout << "No Successor";
	return 0;
}


// #2 
#include<iostream>
#include<stdlib.h>
using namespace std;
struct Node{
	int data;
	Node* left,*right;
};

// Function to return data
Node* getnode(int info){
	Node* p = (Node*)malloc(sizeof(Node));
	p->data = info;
	p->right = NULL;
	p->left = NULL;
	return p;
}
/*
since inorder traversal results in
ascending order visit to node , we
can store the values of the largest
no which is smaller than a (predecessor)
and smallest no which is large than
a (successor) using inorder traversal
*/
void find_p_s(Node* root,int a,
			Node** p, Node** q){
	// If root is null return
	if(!root)
		return ;
	// traverse the left subtree
	find_p_s(root->left, a, p, q);
	// root data is greater than a
	if(root&&root->data > a){	
		// q stores the node whose data is greater
		// than a and is smaller than the previously
		// stored data in *q which is successor
		if((!*q) || (*q) && (*q)->data > root->data)
				*q = root;
	}
	// if the root data is smaller than
	// store it in p which is predecessor
	else if(root && root->data < a){
		*p = root;
	}	
	// traverse the right subtree
	find_p_s(root->right, a, p, q);
}
int main(){
	Node* root1 = getnode(50);
	root1->left = getnode(20);
	root1->right = getnode(60);
	root1->left->left = getnode(10);
	root1->left->right = getnode(30);
	root1->right->left = getnode(55);
	root1->right->right = getnode(70);
	Node* p = NULL, *q = NULL;
	find_p_s(root1, 55, &p, &q);
	if(p)
		cout << p->data;
	if(q)
		cout << " " << q->data;
	return 0;
}
