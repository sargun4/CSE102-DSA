#include <stdio.h>
#include <stdlib.h>
typedef struct AVLNode {
    int data;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
} AVLNode;

AVLNode* createNode(int data) {
    AVLNode* newNode = (AVLNode*)malloc(sizeof(AVLNode));
    newNode->data = data;
    newNode->left = newNode->right=NULL;
    newNode->height = 1;
    return newNode;
}

int getHeight(AVLNode* root) {
    if (root == NULL) {
        return 0;
    }
    return root->height;
}

int getBalanceFactor(AVLNode* root) {
    if (root == NULL) {
        return 0;
    }
    return getHeight(root->left) - getHeight(root->right);
}
AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* t2 = x->right;
    x->right = y;
    y->left = t2;
    y->height = 1 + fmax(getHeight(y->left), getHeight(y->right));
    x->height = 1 + fmax(getHeight(x->left), getHeight(x->right));
    return x;
}
AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* t2 = y->left;
    y->left = x;
    x->right = t2;
    x->height = 1 + fmax(getHeight(x->left), getHeight(x->right));
    y->height = 1 + fmax(getHeight(y->left), getHeight(y->right));
    return y;
}
AVLNode* insert(AVLNode* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    } else {
        return root;
    }
    root->height = 1 + fmax(getHeight(root->left), getHeight(root->right));
    int BF = getBalanceFactor(root);
    if (BF > 1 && data < root->left->data) {
        return rotateRight(root);
    }
    if (BF < -1 && data > root->right->data) {
        return rotateLeft(root);
    }
    if (BF > 1 && data > root->left->data) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (BF < -1 && data < root->right->data) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    return root;
}
AVLNode* minValueNode(AVLNode* root) {
    AVLNode* current = root;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}
AVLNode* deleteNode(AVLNode* root, int data) {
    if (root == NULL) {
        return root;
    }
    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
            // root with only one child or no child
        if (root->left == NULL || root->right == NULL) {
            AVLNode* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
                free(temp);
            }
        } else {
            // root with two children: get the inorder successor (smallest
            // in the right subtree)
            AVLNode* temp = minValueNode(root->right);
            // copy the inorder successor's data to this root
            root->data = temp->data;
            // delete the inorder successor
            root->right = deleteNode(root->right, temp->data);
        }
    }
    if (root == NULL) {
        return root;
    }

    root->height = 1 + fmax(getHeight(root->left), getHeight(root->right));

    int BF = getBalanceFactor(root);

    if (BF > 1 && getBalanceFactor(root->left) >= 0) {
        return rotateRight(root);
    }

    if (BF > 1 && getBalanceFactor(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (BF < -1 && getBalanceFactor(root->right) <= 0) {
        return rotateLeft(root);
    }

    if (BF < -1 && getBalanceFactor(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    return root;
}
void inorderTraversal(AVLNode* root) {
    if (root == NULL) {
    return;
    }
    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}
int main() {
    AVLNode* root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);
    printf("Inorder Traversal: ");
    inorderTraversal(root);
    root = deleteNode(root, 30);
    printf("\nInorder Traversal after deletion: ");
    inorderTraversal(root);
    return 0;
}