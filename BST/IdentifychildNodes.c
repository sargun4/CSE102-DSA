#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include<math.h>
struct node {
    int data;
    struct node* left;
    struct node* right;
};
struct node* createnode(int data) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}
struct node* insert(struct node* root, int data) {
    if (root == NULL) {
        return createnode(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    }
    else {
        root->right = insert(root->right, data);
    }
    return root;
}
struct node* delete(struct node* root, int val) {
    if (root == NULL) {
        return root;
    }
    if (val < root->data) {
        root->left = delete(root->left, val);
    } else if (val > root->data) {
        root->right = delete(root->right, val);
    } else {
        if (root->left == NULL) { //leftchild absent
            struct node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {//rightchild absent
            struct node* temp = root->left;
            free(root);
            return temp;
        }
        struct node* temp = root->right;
        while (temp && temp->left != NULL) {
            temp = temp->left; 
        } //now temp points to minnode
        root->data = temp->data;
        root->right = delete(root->right, temp->data);
    }
    return root;
}
struct node* lca(struct node* root,int n1,int n2){
    if(root==NULL) return NULL;
    if(root->data <n1 && root->data < n2){
        return lca(root->right,n1,n2);
    }
    if(root->data > n1 && root->data > n2){
        return lca(root->right,n1,n2);
    }
}
void bubblesort(int *arr,int len){
    int temp;
    for(int i=0;i<len-1;i++){
        for(int j=0;j<len-1-i;j++){
            if(arr[j]>arr[j+1]){
                temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
}
void printgivenlvl(struct node* root,int lvl){
    if(root==NULL) return;
    if(lvl==1) printf("%d ",root->data);
    else if(lvl>1){
        printgivenlvl(root->left,lvl-1);
        printgivenlvl(root->right,lvl-1);
    }
}