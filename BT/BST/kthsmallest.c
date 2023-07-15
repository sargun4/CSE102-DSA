#include <stdio.h>
#include <stdlib.h>

// define the structure for a binary search tree node
struct node {
    int data;
    struct node* left;
    struct node* right;
};

// create a new node with the given data
struct node* createNode(int data)
{
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// insert a new node with the given data into the tree
struct node* insertNode(struct node* root, int data)
{
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insertNode(root->left, data);
    }
    else if (data > root->data) {
        root->right = insertNode(root->right, data);
    }
    return root;
}

// find the kth smallest node in the tree
void kthSmallestUtil(struct node* root, int k, int* count, struct node** res)
{
    if (root == NULL || *res != NULL) {
        return;
    }
    
    kthSmallestUtil(root->left, k, count, res);
    
    *count = *count + 1;
    if (*count == k) {
        *res = root;
        return;
    }
    
    kthSmallestUtil(root->right, k, count, res);
}

struct node* kthSmallest(struct node* root, int k)
{
    int count = 0;
    struct node* res = NULL;
    kthSmallestUtil(root, k, &count, &res);
    return res;
}

// find the kth largest node in the tree
void kthLargestUtil(struct node* root, int k, int* count, struct node** res)
{
    if (root == NULL || *res != NULL) {
        return;
    }
    
    kthLargestUtil(root->right, k, count, res);
    
    *count = *count + 1;
    if (*count == k) {
        *res = root;
        return;
    }
    
    kthLargestUtil(root->left, k, count, res);
}

struct node* kthLargest(struct node* root, int k)
{
    int count = 0;
    struct node* res = NULL;
    kthLargestUtil(root, k, &count, &res);
    return res;
}
// test the functions with an example tree
int main()
{
    // create a tree with the following nodes: 4, 2, 6, 1, 3, 5, 7
    struct node* root = createNode(4);
    insertNode(root, 2);
    insertNode(root, 6);
    insertNode(root, 1);
    insertNode(root, 3);
    insertNode(root, 5);
    insertNode(root, 7);
    
    // test the kthSmallest function
    int k = 3;
    struct node* kthSmallestNode = kthSmallest(root, k);
    if (kthSmallestNode != NULL) {
        printf("The %dth smallest node is: %d\n", k, kthSmallestNode->data);
    }
    else {
        printf("The BST does not have %d nodes.\n", k);
    }
    
    // test the kthLargest function
    k = 5;
    struct node* kthLargestNode = kthLargest(root, k);
    if (kthLargestNode != NULL) {
        printf("The %dth largest node is: %d\n", k, kthLargestNode->data);
    }
    else {
        printf("The BST does not have %d nodes.\n", k);
    }
    
    return 0;
}
