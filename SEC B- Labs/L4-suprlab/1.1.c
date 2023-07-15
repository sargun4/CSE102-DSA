#include <stdio.h>
#include <stdlib.h>

// Structure for a binary tree node
struct Node {
    char data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new binary tree node
struct Node* createNode(char value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to check if a given string is a palindrome
int isPalindrome(char* str, int start, int end) {
    while (start < end) {
        if (str[start] != str[end])
            return 0;
        start++;
        end--;
    }
    return 1;
}

// Function to count the number of palindromic paths in the binary tree
int countPalindromicPaths(struct Node* node, char* path, int pathLength) {
    if (node == NULL)
        return 0;

    path[pathLength] = node->data;
    path[pathLength + 1] = '\0';

    int count = 0;
    if (node->left == NULL && node->right == NULL) {
        if (isPalindrome(path, 0, pathLength))
            count = 1;
    }
    else {
        count += countPalindromicPaths(node->left, path, pathLength + 1);
        count += countPalindromicPaths(node->right, path, pathLength + 1);
    }

    return count;
}

int main() {
    int height;
    scanf("%d", &height);

    char nodes[1 << (height + 1)];
    scanf(" ");
    for (int i = 1; i < (1 << (height + 1)); i += 2)
        scanf("%c ", &nodes[i]);

    struct Node* root = createNode(nodes[1]);

    for (int i = 1; i < (1 << height); i++) {
        if (nodes[i] != 'N') {
            struct Node* currNode = createNode(nodes[i]);
            if (i % 2 == 0)
                root->right = currNode;
            else
                root->left = currNode;
        }
        if (i % 2 == 1)
            root = root->left;
    }

    char path[height + 1];
    path[0] = root->data;
    path[1] = '\0';

    int count = countPalindromicPaths(root, path, 0);
    printf("%d\n", count);

    return 0;
}
