#include<stdio.h>
#include<stdlib.h>
// Breadth first=Lvl order trraversal
// DEpth first =pre,in,post;

struct node{
    int data;
    struct node* left,*right;
};

void inorder(struct node* root){
    if(root!=NULL){
        inorder(root->left);
        printf("%d ",root->data);
        inorder(root->right);
    }
}
struct node* createnode(int data){
    struct node* n = malloc(sizeof(struct node));
    n->data = data;
    n->left = NULL;
    n->right = NULL;
    return n;
}

struct node* insert(struct node* root, int val) {
    if (root == NULL) {
        return createnode(val);
    }
    if (val < root->data) {
        root->left = insert(root->left, val);
    }
    else if (val > root->data) {
        root->right = insert(root->right, val);
    }
    return root;
}

// smallest value node in the BST
int minValueNode(struct node* root) {
    struct node* current = root;
    while (current->left != NULL) {
        current = current->left;
    }
    // printf(current);
    return current->data;
}
struct node* maxValueNode(struct node* root) {
    struct node* current = root;
    while (current->right != NULL) {
        current = current->right;
    }
    return current;
}

struct node* deleteNode(struct node* root, int val) {
    // base case: empty tree
    if (root == NULL) {
        return root;
    }
    // search for the node with the val value
    if (val < root->data) {
        root->left = deleteNode(root->left, val);
    }
    else if (val > root->data) {
        root->right = deleteNode(root->right, val);
    }
    else {
        // node found, delete it
        if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }
        // node has two children, find the in-order successor
        struct node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

int main(){
    struct node* root=createnode(1);
    root->left=createnode(2);
    root->right=createnode(3);
    insert(root,4);
    inorder(root);
    printf("\nMinimum value in the tree is: %d\n", minValueNode(root));
    struct node* maxNode = maxValueNode(root);
    printf("Maximum value in the tree is: %d\n", maxNode->data);
    root = deleteNode(root, 2);
    inorder(root);
    return 0;
}
