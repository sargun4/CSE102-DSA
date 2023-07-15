#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 10000

typedef struct node {
    int data;
    struct node* left;
    struct node* right;
} Node;

int main() {
    int n, i, parent_index, left_child_index, right_child_index;
    int arr[MAX_NODES];

    // read input
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // create root node
    Node* root = (Node*)malloc(sizeof(Node));
    root->data = arr[0];
    root->left = NULL;
    root->right = NULL;

    // iterate over the remaining elements of the array and insert them as children of the next available node
    for (i = 1; i < n; i++) {
        // find the parent node
        parent_index = (i - 1) / 2;
        Node* parent = (Node*)malloc(sizeof(Node));
        parent->data = arr[parent_index];

        // find the current node
        Node* current = (Node*)malloc(sizeof(Node));
        current->data = arr[i];
        current->left = NULL;
        current->right = NULL;

        // attach the current node as the left or right child of the parent node
        if (i % 2 == 0) {
            parent->right = current;
        } else {
            parent->left = current;
        }
            // free memory for thecreated nodes, since they are already linked to the tree
        free(parent);
        free(current);
    }
    // print the inorder traversal of the tree
    printf("Inorder traversal of the binary tree is:\n");
    inorder_traversal(root);
    printf("\n");

    // free memory for the root node
    free(root);

    return 0;
}
void inorder_traversal(Node* root) {
    if (root == NULL) {
        return;
    }
    inorder_traversal(root->left);
    printf("%d ", root->data);
    inorder_traversal(root->right);
}