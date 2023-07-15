#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 20
#define MAX_NODES 1000000

typedef struct bst_node {
    char key[MAX_LEN+1];
    struct bst_node *left, *right;
} BSTNode;

int cmp(char *a, char *b) {
    int i;
    for (i = 0; a[i] != '\0' && b[i] != '\0'; i++) {
        if (a[i] < b[i]) {
            return -1;
        } else if (a[i] > b[i]) {
            return 1;
        }
    }
    if (a[i] == '\0' && b[i] == '\0') {
        return 0;
    } else if (a[i] == '\0') {
        return -1;
    } else {
        return 1;
    }
}

BSTNode *create_node(char *key) {
    BSTNode *node = (BSTNode *)malloc(sizeof(BSTNode));
    strcpy(node->key, key);
    node->left = node->right = NULL;
    return node;
}

BSTNode *insert(BSTNode *root, char *key) {
    if (root == NULL) {
        return create_node(key);
    } else if (cmp(key, root->key) < 0) {
        root->left = insert(root->left, key);
    } else {
        root->right = insert(root->right, key);
    }
    return root;
}

void print_prefix(BSTNode *root, char *prefix) {
    if (root == NULL) {
        return;
    }
    int i;
    for (i = 0; i < strlen(prefix); i++) {
        if (prefix[i] != root->key[i]) {
            break;
        }
    }
    if (i == strlen(prefix)) {
        printf("%s\n", root->key);
    }
    if (cmp(prefix, root->key) <= 0) {
        print_prefix(root->left, prefix);
    }
    if (cmp(prefix, root->key) >= 0) {
        print_prefix(root->right, prefix);
    }
}

BSTNode *delete_prefix(BSTNode *root, char *prefix) {
    if (root == NULL) {
        return NULL;
    }
    if (cmp(root->key, prefix) == 0) {
        root->left = delete_prefix(root->left, prefix);
        root->right = delete_prefix(root->right, prefix);
        free(root);
        return NULL;
    } else if (cmp(root->key, prefix) > 0) {
        root->left = delete_prefix(root->left, prefix);
    } else {
        root->right = delete_prefix(root->right, prefix);
    }
    return root;
}

int main() {
    int n, q, i;
    char str[MAX_LEN+1], command[6], prefix[MAX_LEN+1];
    BSTNode *root = NULL;
    scanf("%d %d", &n, &q);
    for (i = 0; i < n; i++) {
        scanf("%s", str);
        root = insert(root, str);
    }
   while (q--) {
        scanf("%s", command);
        if (strcmp(command, "Delete") == 0) {
            scanf("%s", prefix);
            root = delete_prefix(root, prefix);
        } else {
            scanf("%s", prefix);
            print_prefix(root, prefix);
            if (strncmp(root->key, prefix, strlen(prefix)) != 0) {
                printf("-1\n");
            }
        }
    }
    return 0;
}
