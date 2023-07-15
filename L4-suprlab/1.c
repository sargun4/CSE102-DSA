#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// Function to check if a string is a palindrome
int isPalindrome(char* str) {
    int len = strlen(str);
    int i, j;
    for (i = 0, j = len - 1; i < j; i++, j--) {
        if (str[i] != str[j])
            return 0;
    }
    return 1;
}

// Function to count the number of palindromic paths in the binary tree
int countPalindromicPaths(struct Node* root, char* path, int height) {
    if (root == NULL)
        return 0;

    // Append the current node's value to the path string
    path[height] = root->data;
    path[height + 1] = '\0';

    // If it's a leaf node, check if the path is a palindrome
    if (root->left == NULL && root->right == NULL) {
        if (isPalindrome(path))
            return 1;
        else
            return 0;
    }

    // Recursively count palindromic paths in the left and right subtrees
    int leftCount = countPalindromicPaths(root->left, path, height + 1);
    int rightCount = countPalindromicPaths(root->right, path, height + 1);

    return leftCount + rightCount;
}

int main() {
    int height;
    scanf("%d", &height);

    // Read the level order traversal of the binary tree
    char nodes[1 << (height + 1)];
    scanf("%s", nodes);

    struct Node* root = NULL;
    int index = 0;

        // Build the binary tree from the level order traversal
    if (nodes[0] != 'N') {
        root = createNode(nodes[0]);
        index++;
    }

    struct Node* queue[1 << (height + 1)];
    int front = 0, rear = 0;
    queue[rear++] = root;

    // Perform level order traversal to build the binary tree
    while (index < (1 << (height + 1))) {
        struct Node* currNode = queue[front++];
        
        // Process the left child
        if (nodes[index] != 'N') {
            currNode->left = createNode(nodes[index]);
            queue[rear++] = currNode->left;
        }
        index++;

        // Process the right child
        if (index < (1 << (height + 1)) && nodes[index] != 'N') {
            currNode->right = createNode(nodes[index]);
            queue[rear++] = currNode->right;
        }
        index++;
    }

    char path[height + 1];
    path[0] = root->data;
    path[1] = '\0';

    int count = countPalindromicPaths(root, path, 0);
    printf("%d\n", count);

    return 0;
}
