#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left;
    struct node *right;
};
struct node *create_node(int data) {
    struct node *root = (struct node *)malloc(sizeof(struct node));
    root->data = data;
    root->left = NULL;
    root->right = NULL;
    return root;
}
struct node *formtree(int *arr, int n) {
    if (n == 0) {
        return NULL;
    }
    struct node *nodes[n];
    for (int i = 0; i < n; i++) {
        nodes[i] = create_node(arr[i]);
    }
    for (int i = 0; i < n / 2; i++) {
        if (nodes[i] != NULL) {
            if (2 * i + 1 < n && nodes[2 * i + 1]->data != -1) { //left hild
                nodes[i]->left = nodes[2 * i + 1];
            }
            if (2 * i + 2 < n && nodes[2 * i + 2]->data != -1) { //right child
                nodes[i]->right = nodes[2 * i + 2];
            }
        }
    }
    return nodes[0];//root
}

int height(struct node* root) {
    if (root == NULL) {
        return 0;
    }
    int lht = height(root->left);
    int rht = height(root->right);
    if (lht > rht) {
        return lht + 1;
    } else {
        return rht + 1;
    }
}

int max(int a,int b){
    return a>b ? a:b;
}
int diameter(struct node* root) {
    if (root == NULL) {
        return 0;
    }
    int lht = height(root->left);
    int rht = height(root->right);
    int ldiam = diameter(root->left);
    int rdiam = diameter(root->right); 
    return max(lht + rht + 1, max(ldiam, rdiam));
}
int main() {
    int n;
    scanf("%d", &n);
    int *arr = (int *)malloc((2*n+1)* sizeof(int));
    for (int i = 0; i < 2*n+1;i++) {
        scanf("%d", &arr[i]);
    }
    struct node *root = formtree(arr, 2*n+1);
    int h = height(root);
    int d = diameter(root);
    // printf("%d\n",h);
    // printf("%d\n",d);
    printf("%d", abs(h - d));
    return 0;
}
