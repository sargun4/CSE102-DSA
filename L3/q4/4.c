#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char key[21];
    struct Node* left;
    struct Node* right;
} Node;
int str_len(const char* str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

int str_cmp(const char* str1, const char* str2) {
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

int str_n_cmp(const char* str1, const char* str2, int n) {
    int i = 0;
    while (i < n && str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] < str2[i]) {
            return -1;
        } else if (str1[i] > str2[i]) {
            return 1;
        }
        i++;
    }

    if (i == n) {
        return 0;
    } else if (str1[i] == '\0' && str2[i] == '\0') {
        return 0;
    } else if (str1[i] == '\0') {
        return -1;
    } else {
        return 1;
    }
}

void str_cpy(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}
Node* createNode(char* key) {
    Node* node = (Node*)malloc(sizeof(Node));
    str_cpy(node->key, key);
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node* insert(Node* root, char* key) {
    if (root == NULL) {
        return createNode(key);
    }

    if (str_cmp(key, root->key) < 0) {
        root->left = insert(root->left, key);
    } else if (str_cmp(key, root->key) > 0) {
        root->right = insert(root->right, key);
    }

    return root;
}

void inorder(Node* root, char* prefix) {
    if (root == NULL) {
        return;
    }

    inorder(root->left, prefix);

    if (str_n_cmp(root->key, prefix, str_len(prefix)) == 0) {
        printf("%s\n", root->key);
    }

    inorder(root->right, prefix);
}

Node* deletePrefix(Node* root, char* prefix) {
    if (root == NULL) {
        return NULL;
    }

    root->left = deletePrefix(root->left, prefix);
    root->right = deletePrefix(root->right, prefix);

    if (str_n_cmp(root->key, prefix, str_len(prefix)) == 0) {
        free(root);
        return NULL;
    }

    return root;
}

int main() {
    int N, Q;
    scanf("%d %d", &N, &Q);

    Node* root = NULL;

    // Insert strings into the BST
    for (int i = 0; i < N; i++) {
        char key[21];
        scanf("%s", key);
        root = insert(root, key);
    }

    // Process queries
    for (int i = 0; i < Q; i++) {
        char operation[8];
        char prefix[21];
        scanf("%s %s", operation, prefix);

        if (str_cmp(operation, "Find") == 0) {
            inorder(root, prefix);
        } else if (str_cmp(operation, "Delete") == 0) {
            Node* newRoot = deletePrefix(root, prefix);
            if (newRoot == NULL) {
                printf("-1\n");
            }
            root = newRoot;
        }
    }

    return 0;
}
