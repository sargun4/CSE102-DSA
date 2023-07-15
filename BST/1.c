#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct node {
    int data;
    struct node *left;
    struct node *right;
};
struct node* createnode(int data) {
    struct node* node = (struct node*)malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}
struct node* insert(struct node* node, int data) {
    if (node == NULL) {
        return createnode(data);
    }
    if (data < node->data) {
        node->left = insert(node->left, data);
    }
    else {
        node->right = insert(node->right, data);
    }
    return node;
}

struct node* del(struct node* root, int data) {
    if (root == NULL) {
        return NULL;
    }
    if (data < root->data) {
        root->left = del(root->left, data);
    } else if (data > root->data) {
        root->right = del(root->right, data);
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

struct node* minNode(struct node* root) {
    struct node* current = root;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}
struct node* search(struct node* root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }
    if (data < root->data) {
        return search(root->left, data);
    } else {
        return search(root->right, data);
    }
}
void inorder(struct node* root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}
int minValue(struct node* root) {
    struct node* current = root;
    while (current->left != NULL) {
        current = current->left;
    }
    return current->data;
}
int height(struct node* root) {
    if (root == NULL) {
        return 0;
    }
    int lht = height(root->left);
    int rht = height(root->right);
    if (lht > rht) {
        return lht + 1;
    } else {
        return rht + 1;
    }
}
// int isBalanced(struct node* root) {
//     if (root == NULL) {
//         return 1;
//     }
//     int lht = height(root->left);
//     int rht = height(root->right);
//     if (abs(lht - rht) <= 1 && isBalanced(root->left) && isBalanced(root->right){
    //     return 1; }
    // return 0;
// }

int maxValue(struct node* root) {
    struct node* current = root;
    while (current->right != NULL) {
        current = current->right;
    }
    return current->data;
}
int countNodes(struct node* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + countNodes(root->left) + countNodes(root->right);
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

void printPaths(struct node* root, int path[], int pathLen) {
    if (root == NULL) {
        return;
    }
    path[pathLen] = root->data;
    pathLen++;
    if (root->left == NULL && root->right == NULL) {
        for (int i = 0; i < pathLen; i++) {
            printf("%d ", path[i]);
        }
        printf("\node");
    } else {
        printPaths(root->left, path, pathLen);
        printPaths(root->right, path, pathLen);
    }
}
void mirror(struct node* root) {
    if (root == NULL) {
        return;
    }
    mirror(root->left);
    mirror(root->right);
    struct node* temp = root->left;
    root->left = root->right;
    root->right = temp;
}
struct node* lowestCommonAncestor(struct node* root, int n1, int n2) {
    if (root == NULL) {
        return NULL;
    }
    if (root->data > n1 && root->data > n2) {
        return lowestCommonAncestor(root->left, n1, n2);
    }
    if (root->data < n1 && root->data < n2) {
        return lowestCommonAncestor(root->right, n1, n2);
    }
    return root;
}

bool areIdentical(struct node* root1, struct node* root2) {
    if (root1 == NULL && root2 == NULL) {
        return true;
    }
    if (root1 == NULL || root2 == NULL) {
        return false;
    }
    if (root1->data != root2->data) {
        return false;
    }
    return areIdentical(root1->left, root2->left) && areIdentical(root1->right, root2->right);
}
int height(struct node* root) {
    if (root == NULL) {
        return 0;
    }
    int lht = height(root->left);
    int rht = height(root->right);
    return (lht > rht ? lht : rht) + 1;
}

bool isBalanced(struct node* root) {
    if (root == NULL) {
        return true;
    }
    int lht = height(root->left);
    int rht = height(root->right);
    return (abs(lht - rht) <= 1) && isBalanced(root->left) && isBalanced(root->right);
}

int diameter(struct node* root) {
    if (root == NULL) {
        return 0;
    }
    int lht = height(root->left);
    int rht = height(root->right);
    int leftDiameter = diameter(root->left);
    int rightDiameter = diameter(root->right);
    return max(lht + rht + 1, max(leftDiameter, rightDiameter));
}

void kthSmallestUtil(struct node* root, int k, int* count, int* result) {
    if (root == NULL || *count >= k) {
        return;
    }
    kthSmallestUtil(root->left, k, count, result);
    (*count)++;
    if (*count == k) {
        *result = root->data;
        return;
    }
    kthSmallestUtil(root->right, k, count, result);
}
int kthSmallest(struct node* root, int k) {
    int count = 0, result = INT_MIN;
    kthSmallestUtil(root, k, &count, &result);
    return result;
}

struct node* leafDelete(struct node* root){
    if (root == NULL)
        return NULL;
    if (root->left == NULL && root->right == NULL) {
        free(root);
        return NULL;
    }
    // Else recursively delete in left and rightsubtrees.
    root->left = leafDelete(root->left);
    root->right = leafDelete(root->right);
    return root;
}