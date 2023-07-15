// diameter-longest path bw 2 nodes
#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node* left,*right;
};
int diameter(struct node* root){
    int diam=0;
    height(root,diam);
    return diam;
}
int height(struct node* root,int diam){
    if(!root) return 0;
    int lh=height(root->left,diam);
    int rh=height(root->right,diam);
    diam=max(diam,lh+rh);
    return 1+max(lh,rh);
}

struct node* del(struct node* root,int data){
    if(root==NULL) return root;
    else if(data<root->data) root->left=del(root->left,data);
    else if(data>root->data) root->right=del(root->right,data);
    else{
        // case1- no child
        if(root->left==NULL && root->right==NULL){
            free(root);
            root=NULL;
            return root;  }
        //case2- one child
        else if(root->left==NULL){
            struct node *temp=root;
            root=root->right;
            free(temp);
            return root;  }
              

    }
}
