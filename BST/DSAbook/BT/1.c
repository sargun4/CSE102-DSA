#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    struct node* left,*right;
};

struct node* createnode(int data) {
    struct node* root = (struct node*)malloc(sizeof(struct node));
    root->data = data;
    root->left = NULL;
    root->right = NULL;
    return root;
}
struct node* insert(struct node* root, int data) {
    if (root == NULL) {
        return createnode(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    }
    else {
        root->right = insert(root->right, data);
    }
    return root;
}

int count_nodes(struct node* root) {
    if (root == NULL) {
        return 0;
    }
    return count_nodes(root->left) + count_nodes(root->right) + 1;
}
struct node* minNode(struct node* root) {
    struct node* current = root;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}
struct node* del(struct node* root, int val) {
    if (root == NULL) {
        return NULL;
    }
    if (val < root->data) {
        root->left = del(root->left, val);
    } else if (val > root->data) {
        root->right = del(root->right, val);
    } else {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        } else if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        } else {
            struct node* temp = minNode(root->right);
            root->data = temp->data;
            root->right = del(root->right, temp->data);
        }
    }
    return root;
}

void preorder(struct node* root){
    if(root!=NULL){
        printf("%d ",root->data);
        preorder(root->left);
        preorder(root->right);
    }
}
int height(struct node* root) {
    if (root == NULL) {
        return 0;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    if (leftHeight > rightHeight) {
        return leftHeight + 1;
    } else {
        return rightHeight + 1;
    }
}
int calculate_height(struct node* root) {
    if (root == NULL)  return 0;
    int left_height = calculate_height(root->left);
    int right_height = calculate_height(root->right);
    return (left_height > right_height ? left_height : right_height) + 1;
}
int maxnode(struct node*root){
    struct node* maxi=root;
    while(maxi && maxi->right!=NULL){
        maxi=maxi->right;
    }
    return maxi->data;
}
struct node* mirror(struct node *root){
    struct node*temp;
    if(root){
        mirror(root->left);
        mirror(root->right);
        // swap nodes
        temp=root->left;
        root->left=root->right;
        root->right=temp;
    }
    return root;
}
int countLeaves(struct node* root) {
    if (root == NULL) {
        return 0;
    }
    if (root->left == NULL && root->right == NULL) {
        return 1;
    } else {
        return countLeaves(root->left) + countLeaves(root->right);
    }
}
int countNonLeaves(struct node* root) {
    if (root == NULL || (root->left == NULL && root->right == NULL)) {
        return 0;
    }
    return 1 + countNonLeaves(root->left) + countNonLeaves(root->right);
}