#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createnode(int data) {
    struct Node* root = (struct Node*)malloc(sizeof(struct Node));
    root->data = data;
    root->left = NULL;
    root->right = NULL;
    return root;
}
struct Node* insert(struct Node* root, int data) {
    if (root == NULL)
        return createnode(data);
    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    return root;
}
struct Node* minValueNode(struct Node* root) {
    struct Node* current = root;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}
struct Node* deleteNode(struct Node* root, int data) {
    if (root == NULL)
        return root;
    if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        struct Node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}
void kthSmallest(struct Node* root, int k, int* count, int* result) {
    if (root != NULL) { //inorder
        kthSmallest(root->left, k, count, result);
        (*count)++;
        if (*count == k) {
            *result = root->data;
        }
        kthSmallest(root->right, k, count, result);
    }
}
int height(struct Node* root) {
    if (root == NULL) {
        return 0;
    } else {
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);
        if (leftHeight > rightHeight) {
            return leftHeight + 1;
        } else {
            return rightHeight + 1;
        }
    }
}
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}
int size(struct Node* root) {
    if (root == NULL) {
        return 0;
    } else {
        return 1 + size(root->left) + size(root->right);
    }
}
struct Node* maxValueNode(struct Node* root) {
    struct Node* current = root;
    while (current->right != NULL) {
        current = current->right;
    }
    return current;
}
int countLeaves(struct Node* root) {
    if (root == NULL) {
        return 0;
    }
    if (root->left == NULL && root->right == NULL) {
        return 1;
    }
    return countLeaves(root->left) + countLeaves(root->right);
}
int isBalanced(struct Node* root) {
    int leftHeight, rightHeight;
    if (root == NULL) {
        return 1;
    }
    leftHeight = height(root->left);
    rightHeight = height(root->right);
    if (abs(leftHeight - rightHeight) <= 1 && isBalanced(root->left) && isBalanced(root->right)) {
        return 1;
    }
    return 0;
}
void printGivenLevel(struct Node* root, int level) {
    if (root == NULL) {
        return;
    }
    if (level == 1) {
        printf("%d ", root->data);
    } else if (level > 1) {
        printGivenLevel(root->left, level - 1);
        printGivenLevel(root->right, level - 1);
    }
}
void printLevelOrder(struct Node* root) {
    int h = height(root);
    for (int i = 1; i <= h; i++) {
        printGivenLevel(root, i);
    }
}
struct Node* lca(struct Node* root, int n1, int n2){
    // struct Node* root;
    if (root == NULL)
        return NULL; 
    // If both n1 and n2 are smaller than root, then LCA
    // lies in left
    if (root->data > n1 && root->data > n2)
        return lca(root->left, n1, n2);
    // If both n1 and n2 are greater than root, then LCA
    // lies in right
    if (root->data < n1 && root->data < n2)
        return lca(root->right, n1, n2);
    return root;
}
int distanceFromRoot(struct Node* root, int x){
    if (root->data == x)
        return 0;
    else if (root->data > x)
        return 1 + distanceFromRoot(root->left, x);
    return 1 + distanceFromRoot(root->right, x);
}
 
// Returns minimum distance between a and b.
// This function assumes that a and b exist in BST.
int distanceBetween2(struct Node* root, int a, int b){
    if (!root)
        return 0;
    // Both keys lie in left
    if (root->data > a && root->data > b)
        return distanceBetween2(root->left, a, b);

    // Both keys lie in right
    if (root->data < a && root->data < b) // same path
        return distanceBetween2(root->right, a, b);
 
    // Lie in opposite directions (Root is
    // LCA of two nodes)
    if (root->data >= a && root->data <= b)
        return distanceFromRoot(root, a) +
               distanceFromRoot(root, b);
}
 
// This function make sure that a is smaller
// than b before making a call to findDistWrapper()
// int findDistWrapper(struct Node *root, int a, int b){
//    if (a > b)
//      swap(a, b);
//    return distanceBetween2(root, a, b);  
// }

int main() {
    struct Node* root = NULL;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    printf("Inorder traversal of the binary search tree is: ");
    inorder(root);

    // int searchData = 60;
    // struct Node* result = search(root, searchData);
    // if (result != NULL) {
    //     printf("\n%d is present in the binary search tree", searchData);
    // } else {
    //     printf("\n%d is not present in the binary search tree", searchData);
    // }

    // int n1 = 10, n2 = 14;
    // struct Node* t = lca(root, n1, n2);
    // printf("LCA of %d and %d is %d \n", n1, n2, t->data);
 
    // n1 = 14, n2 = 8;
    // t = lca(root, n1, n2);
    // printf("LCA of %d and %d is %d \n", n1, n2, t->data);
 
    // n1 = 10, n2 = 22;
    // t = lca(root, n1, n2);
    // printf("LCA of %d and %d is %d \n", n1, n2, t->data);
 
    // getchar();
    return 0;

    // int k = 4;
}