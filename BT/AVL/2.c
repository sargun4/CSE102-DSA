#include<stdio.h>
#include<stdlib.h>

struct avlnode{
    struct avlnode* left;
    struct avlnode*right;
    int data;
    int height;
};
int height(struct avlnode* root){
    if(root==NULL) return 0;
    return root->height;
}
int max(int a,int b){
    return(a>b) ? a:b;
}
int BF(struct avlnode* root){
    if(root==NULL) return 0;
    return height(root->left)-height(root->right);
}
struct avlnode*minvalode(struct avlnode* root){
    struct avlnode* curr=root;
    while(curr->left!=NULL){
        curr=curr->left;
    }return curr;
}
struct avlnode *createnode(int data){
    struct avlnode*temp=(struct avlnode*)malloc(sizeof(struct avlnode));
    temp->left=temp->right=NULL;
    temp->data=0;
    temp->height=1;
    return temp;
}
/*   x
      \
       y
      / \
     T2  T1    */ 
struct avlnode*leftrotate(struct avlnode *x){
    struct avlnode *y=x->right;
    struct avlnode *T2=y->left;
    y->left=x;
    x->right=T2;
    x->height=max(height(x->left),height(x->right))+1;
    y->height=max(height(y->left),height(y->right))+1;    
    return y;
}
struct avlnode *rightrotate(struct avlnode *y){
    struct avlnode *x=y->left;
    struct avlnode *T2=x->right;
    x->right=y;
    y->left=T2;
    y->height=max(height(y->left),height(y->right))+1;
    x->height=max(height(x->left),height(x->right))+1;    
    return x;
}
struct avlnode*insert(struct avlnode* root,int data){
    if(root==NULL) return createnode(data);
    if(data<root->data) root->left=insert(root->left,data);
    else if(data > root->data) root->right=insert(root->right,data);
    else return root;

    root->height=1+max(height(root->left),height(root->right));
    int balance_factor=BF(root);
    //4case-rotation
    if(balance_factor>1 && data < root->left->data) //LL
        return rightrotate(root);
    if(balance_factor<-1 && data>root->right->data) //RR
        return leftrotate(root);
    if(balance_factor>1 && data>root->left->data) //LR
        root->left=leftrotate(root->left);
        return rightrotate(root);
    if(balance_factor<-1 && data<root->right->data) //RL
        root->right=rightrotate(root->right);
        return leftrotate(root);
    return root;
}

struct avlnode *delete(struct avlnode*root,int data){
    if(root==NULL) return root;
    if(data<root->data) root->left=delete(root->left,data);
    else if(data> root->data) root->right=delete(root->right,data);
    else{ //node found
        if((root->left==NULL) || (root->right==NULL)){
            struct avlnode* temp=root->left ?root->right:root->right;
            if(temp==NULL) {//node to be delted is leaf node-has zero children
                temp=root;
                root=NULL;
            }
            else{ //node to be deleted has 1 child
                *root=*temp;
            }
            free(temp);
        }
        else{//node has 2 childrn
            struct avlnode* temp=minvalode(root->right);
            root->data=temp->data;
            root->right=delete(root->right,temp->data);
        }
    }
}
void inorder(struct avlnode *root){
    if(root!=NULL){
        inorder(root->left);
        printf("%d ",root->data);
        inorder(root->right);
    }
}
int main(){
    struct avlnode*root=NULL;
    int val,ch;
    while(1){
        printf("\n1.Insert\n2.Delete\n3.Display\n4.EXIt\nEnter choice: ");
        scanf("%d ",&ch);
        switch(ch){
            case 1:
                printf("\nEnter val : ");
                scanf("%d",&val);
                Output:
                root=insert(root,val);
                break;
            case 2:
                printf("\nEnter val : ");
                scanf("%d",&val);
                root=delete(root,val);
                break;
            case 3:
                printf("\nINorder: ");
                inorder(root);
                break;
            case 4:
                exit(0);
                break;
        }
    }return 0;
}