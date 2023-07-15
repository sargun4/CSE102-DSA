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
 
void inorder(struct node* root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    printf("%d ",root->data);
    inorder(root->right);
} 
struct node* minValueNode(struct node* root) {
    struct node* current = root;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}
struct node* maxValueNode(struct node* root) {
    struct node* current = root;
    while (current->right != NULL) {
        current = current->right;
    }
    return current;
}
struct node* search(struct node* root, int key) {
    if (root == NULL || root->data == key) {
        return root;
    }
    if (key < root->data) {
        return search(root->left, key);
    }
    return search(root->right, key);
}
struct node* successor(struct node* root, int key) {
    struct node* current = search(root, key);
    if (current == NULL) {
        return NULL;
    }
    if (current->right != NULL) {
        return minValueNode(current->right);
    }
    struct node* successor = NULL;
    struct node* ancestor = root;
    while (ancestor != current) {
        if (current->data < ancestor->data) {
            successor = ancestor;
            ancestor = ancestor->left;
        }
        else {
            ancestor = ancestor->right;
        }
    }
    return successor;
}
 
struct node* predecessor(struct node* root, int key) {
    struct node* current = search(root, key);
    if (current == NULL) {
        return NULL;
    }
    if (current->left != NULL) {
        return maxValueNode(current->left);
    }
    struct node* predecessor = NULL;
    struct node* ancestor = root;
    while (ancestor != current) {
        if (current->data > ancestor->data) {
            predecessor = ancestor;
            ancestor = ancestor->right;
        }
        else {
            ancestor = ancestor->left;
        }
    }
    return predecessor;
}
int main(){
    struct node* root = NULL;
    int keys[] = { 20, 8, 22, 4, 12, 10, 14 };
    int len = sizeof(keys) / sizeof(keys[0]);
    for (int i = 0; i < len; i++) {
        root = insert(root, keys[i]);
    }
    inorder(root);
    struct node* successor_node = successor(root, 20);
    if (successor_node == NULL) {
        printf("\nNo successor found");
    } else {
        printf("\nSuccessor: %d", successor_node->data);
    }
    
    struct node* predecessor_node = predecessor(root, 20);
    if (predecessor_node == NULL) {
        printf("\nNo predecessor found");
    } else {
        printf("\npredecessor: %d", predecessor_node->data);
    }
    return 0;
}

