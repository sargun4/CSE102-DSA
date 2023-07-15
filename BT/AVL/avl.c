// AVL=Height balanced BSTs
// BF(balanced factor)=Ht. of Right subtree- Ht. of Left subtree
// can be -1,0,1 for a node to be balanced in BST
// for any tree to be balanced, |BF|<=1
#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node* left,*right;
    int height;
};
int getHeight(struct node* root){
    if(root==NULL){
        return 0;
    }return root->height;
}
struct node* createnode(int data){
    struct node* root=malloc(sizeof(struct node));
    root->data=data;
    root->right=root->left=NULL;
    root->height=1;
    return root;
}
int balance_factor(struct node* root){
    if(root==NULL){
        return 0;
    }
    return getHeight(root->left)-getHeight(root->right);
}
int max(int a,int b){
    return a>b?a:b;
}
struct node* rightrotate(struct node* y){
    struct node* x=y->left;
    struct node* T2=x->right;
    x->right=y;
    y->left=T2;
    y->height=max(getHeight(y->right),getHeight(y->left))+1;
    x->height=max(getHeight(x->right),getHeight(x->left))+1; 
    return x;   
}
struct node* leftrotate(struct node* x){
    struct node* y=x->right;
    struct node* T2=y->left;
    x->right=T2;
    y->left=x;
    y->height=max(getHeight(y->right),getHeight(y->left))+1;
    x->height=max(getHeight(x->right),getHeight(x->left))+1; 
    return y;   
}
struct node*insert(struct node* root,int data){
    if(root==NULL) return createnode(data);
    if(data< root->data){
        root->left=insert(root->left,data);
    }else if(data > root->data){
        root->right=insert(root->right,data);
        return root;
    }
    root->height=1+max(getHeight(root->left),getHeight(root->right));
    int bf=balance_factor(root);
    // left-left case
    if(bf>1 && data < root->left->data){
        return rightrotate(root);
    }
    // right-right case
    if(bf<-1 && data > root->left->data){
       return leftrotate(root);
    }
    // left-right case
    if(bf>1 && data > root->left->data){
        root->left=leftrotate(root->left);
        return rightrotate(root);
    }
    // right-left case
    if(bf<-1 && data < root->right->data){
        root->right=leftrotate(root->right);
        return leftrotate(root);
    }
    return root;
}
int main(){
    struct node* root=NULL;
    root=insert(root,1);
    root=insert(root,2);
    root=insert(root,4);
    root=insert(root,5);
    root=insert(root,6);
    root=insert(root,3);
    preorder(root);
    return 0;
}