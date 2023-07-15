#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    int height;
    struct node* left;
    struct node* right;
};

struct node* createNode(int value) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = value;
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int getHeight(struct node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

int getBalanceFactor(struct node* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

int isAVLTree(struct node* root) {
    if (root == NULL)
        return 1;

    int balanceFactor = getBalanceFactor(root);
    if (balanceFactor > 1 || balanceFactor < -1)
        return 0;

    return isAVLTree(root->left) && isAVLTree(root->right);
}

int main() {
    int n;
    scanf("%d", &n);

    struct node* nodes[n + 1];
    nodes[0] = NULL;


    for (int i = 1; i <= n; i++) {
        int value;
        scanf("%d", &value);
        if (value == -1)
            nodes[i] = NULL;
        else
            nodes[i] = createNode(value);
    }


    for (int i = 1; i <= n; i++) {
        if (nodes[i] != NULL) {
            if (2 * i <= n)
                nodes[i]->left = nodes[2 * i];
            if (2 * i + 1 <= n)
                nodes[i]->right = nodes[2 * i + 1];
        }
    }

    struct node* root = nodes[1];

    if (isAVLTree(root))
        printf("YES\n");
    else
        printf("NO\n");

    return 0;
}
