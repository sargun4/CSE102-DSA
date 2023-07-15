#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char *key;
    struct node *left;
    struct node *right;
};

// Create a new node
struct node *new_node(char *key) {
    struct node *new = (struct node*)malloc(sizeof(struct node));
    new->key = (char*)malloc((strlen(key) + 1) * sizeof(char));
    strcpy(new->key, key);
    new->left = NULL;
    new->right = NULL;
    return new;
}

// Insert a new node in the BST
struct node *insert(struct node *root, char *key) {
    if (root == NULL) {
        return new_node(key);
    }
    int cmp = strcmp(key, root->key);
    if (cmp < 0) {
        root->left = insert(root->left, key);
    } else if (cmp > 0) {
        root->right = insert(root->right, key);
    }
    return root;
}
// Free the memory used by the BST
void free_tree(struct node *root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root->key);
    free(root);
}
struct node *delete_prefix(struct node *root, char *prefix) {
    if (!root) {
        return NULL;
    }
    if (prefix[0] < root->key[0]) {
        root->left = delete_prefix(root->left, prefix);
    } else if (prefix[0] > root->key[0]) {
        root->right = delete_prefix(root->right, prefix);
    } else {
        if (strcmp(root->key, prefix) == 0) {
            root = delete_node(root);
        } else {
            root->left = delete_prefix(root->left, prefix);
            root->right = delete_prefix(root->right, prefix);
        }
    }
    return root;
}

// // Delete nodes with the prefix "pref"
// struct node *delete_prefix(struct node *root, char *pref) {
//     if (root == NULL) {
//         return NULL;
//     }
//     int cmp = strncmp(pref, root->key, strlen(pref));
//     if (cmp < 0) {
//         root->left = delete_prefix(root->left, pref);
//     } else if (cmp > 0) {
//         root->right = delete_prefix(root->right, pref);
//     } else {
//         if (root->left == NULL) {
//             struct node *temp = root->right;
//             free(root->key);
//             free(root);
//             return temp;
//         } else if (root->right == NULL) {
//             struct node *temp = root->left;
//             free(root->key);
//             free(root);
//             return temp;
//         } else {
//             struct node *curr = root->right;
//             while (curr->left != NULL) {
//                 curr = curr->left;
//             }
//             free(root->key);
//             root->key = (char*)malloc((strlen(curr->key) + 1) * sizeof(char));
//             strcpy(root->key, curr->key);
//             root->right = delete_prefix(root->right, curr->key);
//         }
//     }
//     return root;
// }


// Print the strings with prefix "pref" in lexicographically sorted order
int print_prefix(struct node *root, char *pref) {
    if (root == NULL) {
        return 0;
    }
    int cmp = strncmp(pref, root->key, strlen(pref));
    if (cmp < 0) {
        return print_prefix(root->left, pref);
    } else if (cmp == 0) {
        int found = print_prefix(root->left, pref);
        printf("%s\n", root->key);
        found |= print_prefix(root->right, pref);
        return found | 1;
    } else {
        return print_prefix(root->right, pref);
    }
}


int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    struct node *root = NULL;

    // Insert N unique strings
    char key[21];
    for (int i = 0; i < n; i++) {
        scanf("%s", key);
        root = insert(root, key);
    }
    // Process queries
    char pref[21];
    for (int i = 0; i < q; i++) {
        scanf("%s", pref);
        if (strcmp(pref, "Find") == 0) {
            scanf("%s", pref);
            if (!print_prefix(root, pref)) {
                printf("-1\n");
            }
        } else if (strcmp(pref, "Delete") == 0) {
            scanf("%s", pref);
            root = delete_prefix(root, pref);
            if (!root) {
                printf("-1\n");
            }
        }
    }


    // Free memory and return
    free_tree(root);
    return 0;
}
