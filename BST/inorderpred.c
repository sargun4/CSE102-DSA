#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node* left,*right;
};
struct node* createnode(int data){
    struct node* temp=(struct node*)malloc(sizeof(struct node));
    temp->data=data;
    temp->left=temp->right=NULL;
    return temp;
}
struct node* insert(struct node* root, int data) {
    if (root == NULL) {
        return createnode(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }
    return root;
}
// rightmost child of left subtree
struct node* inpre(struct node* root){
    struct node* p=root->left;
    while(p->right!=NULL) p=p->right;
    return p;
}
// leftmost child of right subtree
struct node* insuc(struct node* root){
    struct node* p=root->right;
    while(p->left!=NULL) p=p->left;
    return p;
}
void findPreSuc(struct node* root, struct node** pre, struct node** suc, int data) {
    if (!root)
        return;

    if (root->data == data) {
        if (root->left)
            *pre = inpre(root);
        if (root->right)
            *suc = insuc(root);
        return;
    }

    if (root->data > data) {
        *suc = root;
        findPreSuc(root->left, pre, suc, data);
    } else {
        *pre = root;
        findPreSuc(root->right, pre, suc, data);
    }
}
void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
struct node* del(struct node* root, int data){
    if(!root) return NULL;
    if(data > root->data) root->right = del(root->right, data);
    else if(data < root->data) root->left = del(root->left, data);
    else{
        if(root->right == NULL){
            struct node* temp = root->left;
            free(root); return temp;
        }else if(root->left == NULL){
            struct node* temp = root->right;
            free(root); return temp;
        }else{
            struct node* temp = insuc(root);
            swap(&(root->data), &(temp->data));
            root->right = del(root->right, data);
        }
    }
    return root;
}

void inorder(struct node* root){
    if(root!=NULL){
        inorder(root->left);
        printf("%d ",root->data);
        inorder(root->right);
    } 
}

int main() {
    struct node* root = NULL;
    root = insert(root, 50);
    for(int i = 0; i < 8; i++){
        insert(root, 10 * i);
    }
    inorder(root);
    printf("\n");
    del(root, 10);
    inorder(root);
    printf("\n");
    struct node* pre = NULL;
    struct node* suc = NULL;
    int data = 50;
    findPreSuc(root, &pre, &suc, data);
    if (pre != NULL)
        printf("Predecessor of %d is %d\n", data, pre->data);
    else
        printf("No predecessor found for %d\n", data);
    if (suc != NULL)
        printf("Successor of %d is %d\n", data, suc->data);
    else
        printf("No successor found for %d\n", data);
    
    
    return 0;
}
