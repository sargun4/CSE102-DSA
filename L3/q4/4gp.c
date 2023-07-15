#include <stdio.h>
#include <stdlib.h>
// #include <string.h>

#define MAX_LEN 20
#define MAX_NODES 1000000

struct node {
    char key[MAX_LEN+1];
    struct node *left, *right;
};
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

struct node *create_node(char *key) {
    struct node *root = (struct node *)malloc(sizeof(struct node));
    str_cpy(root->key, key);
    root->left = root->right = NULL;
    return root;
}

struct node *insert(struct node *root, char *key) {
    if (root == NULL) {
        return create_node(key);
    } else if (str_cmp(key, root->key) < 0) {
        root->left = insert(root->left, key);
    } else {
        root->right = insert(root->right, key);
    }
    return root;
}

void print_prefix(struct node *root, char *prefix) {
    if (root == NULL) {
        return;
    }
    if (str_n_cmp(root->key, prefix, str_len(prefix)) >= 0) {
        print_prefix(root->left, prefix);
    }
    if (str_n_cmp(root->key, prefix, str_len(prefix)) == 0) {
        printf("%s\n", root->key);
    }
    if (str_n_cmp(root->key, prefix, str_len(prefix)) <= 0) {
        print_prefix(root->right, prefix);
    }
}
struct node *delete_prefix(struct node *root, char *prefix, int *deleted) {
    if (root == NULL) {
        return NULL;
    }
    if (str_n_cmp(root->key, prefix, str_len(prefix)) == 0) {
        *deleted = 1; // set the flag to 1 since a node is deleted
        root->left = delete_prefix(root->left, prefix, deleted);
        root->right = delete_prefix(root->right, prefix, deleted);
        free(root);
        return NULL;
    } else if (str_n_cmp(root->key, prefix, str_len(prefix)) > 0) {
        root->left = delete_prefix(root->left, prefix, deleted);
    } else {
        root->right = delete_prefix(root->right, prefix, deleted);
    }
    return root;
}

int main() {
    int n, q, i;
    char str[MAX_LEN+1], command[6], prefix[MAX_LEN+1];
    struct node *root = NULL;
    scanf("%d %d", &n, &q);
    for (i = 0; i < n; i++) {
        scanf("%s", str);
        root = insert(root, str);
    }

    while (q--) {
        scanf("%s", command);
        if (str_cmp(command, "Delete") == 0) {
            scanf("%s", prefix);
            int deleted = 0; // initialize the flag variable to 0
            root = delete_prefix(root, prefix, &deleted);
            if (!deleted) { // print -1 if no node is deleted
                printf("-1\n");
            }
        } else if (str_cmp(command, "Find") == 0) {
            scanf("%s", prefix);
            if (!root || str_n_cmp(root->key, prefix, str_len(prefix)) != 0) {
                printf("-1\n");
            } else {
                print_prefix(root, prefix);
            }
        }
    }
    return 0;
}
