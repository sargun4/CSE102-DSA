#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 20
#define MAX_NODES 1000000

struct node {
    char key[MAX_LEN + 1];
    struct node* left;
    struct node* right;
};

int myStrlen(const char* str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

int myStrcmp(const char* str1, const char* str2) {
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

int myStrncmp(const char* str1, const char* str2, int n) {
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

void myStrcpy(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}
struct node* createNode(const char* key) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    myStrcpy(newNode->key, key);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct node* insert(struct node* root, const char* key) {
    if (root == NULL) {
        return createNode(key);
    }

    int cmpResult = myStrcmp(key, root->key);
    if (cmpResult < 0) {
        root->left = insert(root->left, key);
    } else if (cmpResult > 0) {
        root->right = insert(root->right, key);
    }

    return root;
}

struct node* findMin(struct node* root) {
    if (root == NULL) {
        return NULL;
    }
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

struct node* deleteNode(struct node* root, const char* key, int* deleted) {
    if (root == NULL) {
        return NULL;
    }

    int cmpResult = myStrcmp(key, root->key);
    if (cmpResult < 0) {
        root->left = deleteNode(root->left, key, deleted);
    } else if (cmpResult > 0) {        root->right = deleteNode(root->right, key, deleted);
    } else {
        // Key found, delete the node
        *deleted = 1;
        if (root->left == NULL && root->right == NULL) {
            // Case 1: Node has no children
            free(root);
            return NULL;
        } else if (root->left == NULL) {
            // Case 2: Node has only right child
            struct node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            // Case 2: Node has only left child
            struct node* temp = root->left;
            free(root);
            return temp;
        } else {
            // Case 3: Node has both left and right children
            struct node* minRight = findMin(root->right);
            myStrcpy(root->key, minRight->key);
            root->right = deleteNode(root->right, minRight->key, deleted);
        }
    }
    return root;
}

void printPrefix(struct node* root, const char* prefix) {
    if (root == NULL) {
        return;
    }

    int cmpResult = myStrncmp(root->key, prefix, myStrlen(prefix));
    if (cmpResult >= 0) {
        printPrefix(root->left, prefix);
    }
    if (cmpResult == 0) {
        printf("%s\n", root->key);
    }
    if (cmpResult <= 0) {
        printPrefix(root->right, prefix);
    }
}

int main() {
    int n, q, i;
    char str[MAX_LEN + 1], command[6], prefix[MAX_LEN + 1];
    struct node* root = NULL;
    scanf("%d %d", &n, &q);
    for (i = 0; i < n; i++) {
        scanf("%s", str);
        root = insert(root, str);
    }

    while (q--) {
        scanf("%s", command);
        if (myStrcmp(command, "Delete") == 0) {
            scanf("%s", prefix);
            int deleted = 0;
            root = deleteNode(root, prefix, &deleted);
            if (!deleted) {
                printf("-1\n");
            }
        } else if (myStrcmp(command, "Find") == 0) {
            scanf("%s", prefix);
            if (!root || myStrncmp(root->key, prefix, myStrlen(prefix)) != 0) {
                printf("-1\n");
            } else {
                printPrefix(root, prefix);
            }
        }
    }

    return 0;
}

