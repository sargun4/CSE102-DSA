#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    long long int data;
    struct node* left;
    struct node* right;
    int height;
    long long int sum;
};

struct node* createNode(long long int data) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = data;
    temp->left = temp->right = NULL;
    temp->height = 1;
    temp->sum = data;
    return temp;
}

int Height(struct node* root) {
    if (root == NULL)
        return 0;
    return root->height;
}

int max(int a, int b) {
    return a > b ? a : b;
}

void updateHeight(struct node* root) {
    int leftHeight = Height(root->left);
    int rightHeight = Height(root->right);
    root->height = max(leftHeight, rightHeight) + 1;
}

long long int subtreeSum(struct node* root) {
    if (root == NULL)
        return 0;
    return root->sum;
}

void updateSubtreeSum(struct node* root) {
    if (root == NULL)
        return;
    long long int leftSum = (root->left) ? subtreeSum(root->left) : 0;
    long long int rightSum = (root->right) ? subtreeSum(root->right) : 0;
    root->sum = root->data + leftSum + rightSum;
}

struct node* leftRotate(struct node* root) {
    struct node* newRoot = root->right;
    struct node* leftSubtree = newRoot->left;
    newRoot->left = root;
    root->right = leftSubtree;
    updateHeight(root);
    updateHeight(newRoot);
    updateSubtreeSum(root);
    updateSubtreeSum(newRoot);
    return newRoot;
}

struct node* rightRotate(struct node* root) {
    struct node* newRoot = root->left;
    struct node* rightSubtree = newRoot->right;
    newRoot->right = root;
    root->left = rightSubtree;
    updateHeight(root);
    updateHeight(newRoot);
    updateSubtreeSum(root);
    updateSubtreeSum(newRoot);
    return newRoot;
}

int balanceFactor(struct node* root) {
    if (root == NULL)
        return 0;
    return Height(root->left) - Height(root->right);
}

struct node* insert(struct node* root, long long int data, int* leftRots, int* rightRots) {
    if (root == NULL)
        return createNode(data);

    if (data < root->data) {
        *leftRots = 0;
        *rightRots = 0;
        root->left = insert(root->left, data, leftRots, rightRots);
        int BF = balanceFactor(root);

        if (BF > 1) {
            // Left subtree is heavier
            if (data < root->left->data) {
                // LL
                (*rightRots)++;
                root = rightRotate(root);
            } else {
                // LR
                (*leftRots)++;
                root->left = leftRotate(root->left);
                (*rightRots)++;
                root = rightRotate(root);
            }
        }
    } else if (data > root->data) {
        *leftRots = 0;
        *rightRots = 0;
        root->right = insert(root->right, data, leftRots, rightRots);
        int BF = balanceFactor(root);

        if (BF < -1) {
            // Right subtree is heavier
            if (data > root->right->data) {
                // RR
                (*leftRots)++;
                root = leftRotate(root);
            } else {
                // RL
                (*rightRots)++;
                root->right = rightRotate(root->right);
                (*leftRots)++;
                root = leftRotate(root);
            }
        }
    }

    updateHeight(root);
    updateSubtreeSum(root);
    // Reset left and right rotations to 0
    // if (*leftRots > 0 || *rightRots > 0) {
    //     printf("Left Rotations: %d\n", *leftRots);
    //     printf("Right Rotations: %d\n", *rightRots);
    //     *leftRots = 0;
    //     *rightRots = 0;
    // }
    return root;
}

struct node* search(struct node* root, long long int data) {
    if (root == NULL || root->data == data)
        return root;
    if (data < root->data)
        return search(root->left, data);
    else
        return search(root->right, data);
}

int main() {
    int Q;
    scanf("%d", &Q);

    struct node* root = NULL;
    int leftRots = 0;
    int rightRots = 0;

    for (int i = 0; i < Q; i++) {
        char query[10];
        long long int value;
        scanf("%s %lld", query, &value);

        if (strcmp(query, "insert") == 0) {
            root = insert(root, value, &leftRots, &rightRots);
            printf("%d %d\n", leftRots, rightRots);
        } else if (strcmp(query, "subtree") == 0) {
            struct node* tmp = search(root, value);
            if (tmp != NULL)
                printf("%lld\n", subtreeSum(tmp));
            else
                printf("NA\n");
        }
    }

    return 0;
}
