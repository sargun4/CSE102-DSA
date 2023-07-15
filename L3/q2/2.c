// #include <stdio.h>
// #include <stdlib.h>
// # define MAXN 10001
// int  a[MAXN];
// struct node {
//     int data;
//     struct node *left;
//     struct node *right;
// };
// int max(int a,int b){
//     return a>b ? a:b;
// }
// int height(struct node* root){
//     if(root==NULL) return 0;
//     int lht=height(root->left);
//     int rht=height(root->right);
//     if(lht>rht)
//         return lht+1;
//     else 
//         return rht+1;
// }
// int diameter(struct node* root){
//     if (root == NULL)
//         return 0;
//     int lht = height(root->left);
//     int rht = height(root->right);
//     int ldiam = diameter(root->left);
//     int rdiam = diameter(root->right); 
//     return max(lht + rht + 1, max(ldiam, rdiam));
// }
// struct node* createnode(int data){
//     struct node* temp = (struct node*) malloc(sizeof(struct node));
//     temp->data = data;
//     temp->left = NULL;
//     temp->right = NULL;
//     return(temp);
// }

// struct node* buildTree(int n, int a[]){
//     struct node* root = NULL;
//     struct node* nodes[MAXN];
//     for(int i=1; i<=n; i++){
//         nodes[i] = createnode(i);
//     }
//     for(int i=1; i<=n; i++){
//         if(a[i] == -1) continue;
//         if(i == 1) root = nodes[a[i]];
//         if(i%2 == 1) nodes[(i-1)/2]->left = nodes[a[i]];
//         else nodes[(i-1)/2]->right = nodes[a[i]];
//     }
//     return root;
// }

// int main(){
//     int n;
//     scanf("%d", &n);
//     int a[2*n+1];
//     for(int i=1; i<=2*n+1; i++){
//         scanf("%d", &a[i]);
//     }
//     struct node* root = buildTree(n, a);
//     int ht = height(root);
//     int diam = diameter(root);
//     printf("%d\n", abs(ht - diam));
//     return 0;
// }
#include <stdio.h>
#include <stdlib.h>
#define MAXN 10001

int a[MAXN];

struct node {
    int val;
    struct node *left;
    struct node *right;
};

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
    struct node* nodes[n];
    for (int i = 0; i < n; i++) {
        nodes[i] = NULL;
    }
    for (int i = 1; i < 2 * n + 1; i++) {
        scanf("%d", &a[i]);
        if (a[i] != -1) {
            struct node* new_node = (struct node*)malloc(sizeof(struct node));
            new_node->val = a[i];
            new_node->left = NULL;
            new_node->right = NULL;
            nodes[a[i] - 1] = new_node;
        }
        if (i % 2 == 0) {
            nodes[(i - 1) / 2]->right = nodes[a[i]];
        } else if (a[i] != -1) {
            nodes[(i - 1) / 2]->left = nodes[a[i]];
        } else {
            nodes[(i - 1) / 2]->left = NULL;
        }
    }
    struct node* root = nodes[0];
    int ht = height(root);
    printf("%d\n", ht);
    int diam = diameter(root);
    printf("%d\n", diam);
    printf("%d\n", abs(ht - diam));
    return 0;
}
