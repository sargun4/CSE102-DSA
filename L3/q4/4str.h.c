#include <stdio.h>
#include <stdlib.h>
#define MAX_LEN 20
// Custom string comparison function
int str_cmp(char* str1, char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] < str2[i]) {
            return -1;
        } else if (str1[i] > str2[i]) {
            return 1;
        }
        i++;
    }
    if (str1[i] == '\0' && str2[i] == '\0') {
        return 0;
    } else if (str1[i] == '\0') {
        return -1;
    } else {
        return 1;
    }
}

// Struct representing a node in the BST
struct Node {
    char* key;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node with the given key
struct Node* create_node(char* key) {
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Function to insert a new key into the BST
struct Node* insert(struct Node* root, char* key) {
    if (root == NULL) {
        return create_node(key);
    }
    if (str_cmp(key, root->key) < 0) {
        root->left = insert(root->left, key);
    } else {
        root->right = insert(root->right, key);
    }
    return root;
}

// Function to find all keys with the given prefix
void find_prefix(struct Node* root, char* prefix) {
    if (root == NULL) {
        return;
    }
    if (str_cmp(prefix, root->key) <= 0) {
        find_prefix(root->left, prefix);
    }
    if (prefix[0] == root->key[0]) {
        if (str_cmp(root->key, prefix) >= 0) {
            printf("%s\n", root->key);
        }
    }
    if (str_cmp(prefix, root->key) >= 0) {
        find_prefix(root->right, prefix);
    }
}
// Function to delete a node with the given key
struct Node* deleteNode(struct Node* root, char* key) {
    if (root == NULL) {
        return NULL;
    }
    if (str_cmp(key, root->key) < 0) {
        root->left = deleteNode(root->left, key);
    } else if (str_cmp(key, root->key) > 0) {
        root->right = deleteNode(root->right, key);
    } else {
        // Key matches current node, delete it and its subtrees
        if (root->left == NULL && root->right == NULL) {
            // Case 1: leaf node
            free(root);
            return NULL;
        } else if (root->left == NULL || root->right == NULL) {
            // Case 2: node with one child
            struct Node* child;
            if (root->left != NULL) {
                child = root->left;
            } else {
                child = root->right;
            }
            free(root);
            return child;
        } else {
            // Case 3: node with two children
            // Find the inorder successor (minimum value in right subtree)
            struct Node* successor = root->right;
            while (successor->left != NULL) {
                successor = successor->left;
            }
            // Copy the inorder successor's content to this node
            copy(root->key, successor->key);
            // Recursively delete the inorder successor
            root->right = deleteNode(root->right, successor->key);
        }
        return root;
    }
}

// Function to check if str1 is lexicographically smaller than str2
int isSmaller(char* str1, char* str2) {
    return str_cmp(str1, str2) < 0;
}
size_t strlen(const char* str) {
    const char* p = str;
    while (*p != '\0') {
        p++;
    }
    return p - str;
}

int strncmp(const char* str1, const char* str2, size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (str1[i] == '\0' || str2[i] == '\0' || str1[i] != str2[i]) {
            return (int)(str1[i] - str2[i]);
        }
    }
    return 0;
}
// Function to check if str starts with prefix
int startsWith(char* str, char* prefix) {
    int prefix_len = strlen(prefix);
    if (strncmp(str, prefix, prefix_len) == 0) {
        return 1;
    } else {
        return 0;
    }
}

// Function to check if the BST contains a node with the given key
int contains(struct Node* root, char* key) {
    if (root == NULL) {
        return 0;
    }
    if (str_cmp(key, root->key) == 0) {
        return 1;
    } else if (str_cmp(key, root->key) < 0) {
        return contains(root->left, key);
    } else {
        return contains(root->right, key);
    }
}

// Function to copy the contents of src to dest
void copy(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}


// Function to delete all nodes with the given prefix
void deletePrefix(struct Node* root, char* prefix) {
    if (root == NULL) {
        return;
    }
    // Traverse left subtree if prefix is lexicographically smaller than root's key
    if (isSmaller(prefix, root->key)) {
        deletePrefix(root->left, prefix);
    }
    // If root's key starts with prefix, delete root and traverse right subtree
    if (startsWith(root->key, prefix)) {
        deleteNode(root, root->key);
        deletePrefix(root, prefix);
    }
    // Traverse right subtree if prefix is lexicographically greater than root's key
    if (isSmaller(root->key, prefix)) {
        deletePrefix(root->right, prefix);
        }
    }
    // Function to print all keys with the given prefix in lexicographically sorted order
void printKeysWithPrefix(struct Node* root, char* prefix) {
    if (root == NULL) {
    return;
    }
    // Traverse left subtree if prefix is lexicographically smaller than root's key
    if (isSmaller(prefix, root->key)) {
        printKeysWithPrefix(root->left, prefix);
    }
    // If root's key starts with prefix, print it and traverse right subtree
    if (startsWith(root->key, prefix)) {
        printf("%s\n", root->key);
        printKeysWithPrefix(root->right, prefix);
    }
    // Traverse right subtree if prefix is lexicographically greater than root's key
    if (isSmaller(root->key, prefix)) {
        printKeysWithPrefix(root->right, prefix);
    }
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    struct Node* root = NULL;
    // Insert n unique strings into the BST
    for (int i = 0; i < n; i++) {
        char key[MAX_LEN];
        scanf("%s", key);
        if (!contains(root, key)) {
        root = insert(root, key);
        }
    }
    // Perform q queries on the BST
    for (int i = 0; i < q; i++) {
    char op[10], prefix[MAX_LEN];
    scanf("%s %s", op, prefix);
    if (str_cmp(op, "Delete") == 0) {
        deletePrefix(root, prefix);
    } else if (str_cmp(op, "Find") == 0) {
        find_prefix(root, prefix);
        if (node == NULL) {
        printf("-1\n");
        } else {
            printKeysWithPrefix(node, prefix);
            }
        }
    }
    return 0;
}




