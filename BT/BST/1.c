// BST is a  type of BT with prop-
// 1.All nodes of left subtree are lesser than root & nodes of right subtree r greater than root of that subtree
// 2.Left n right subtree are also BSTs
// 3.no duplicate nodes
// 4.INorder traversal of a BST gives ascending sorted array;

#include <stdio.h>
#include<malloc.h>
struct node{
    int data;
    struct node* left;
    struct node* right;  
};
struct node* createnode(int data){
    struct node *n; // node ptr created
    n=malloc(sizeof(struct node));
    n->data=data;
    n->left=NULL;
    n->right=NULL;
    return n;
}

void inorder(struct node* root){
    if(root!=NULL){
        inorder(root->left);
        printf("%d ",root->data);
        inorder(root->right);
    }
}
int isBST(struct node* root){
    static struct node* prev=NULL;
    if(root!=NULL){
        if(!isBST(root->left)){
            return 0;
        }
        if(prev!=NULL && root->data <= prev->data){
            return 0;
        }
        prev=root;
        return isBST(root->right);
    }else return 1;
}
struct node* search(struct node* root,int key){
    if(root==NULL){
        return NULL;
    }if(root->data==key){
        return root;
    }else if(root->data>key){
        return search(root->left,key);
    }else if(root->data<key){
        return search(root->right,key);
    }
}
struct node* searchiter(struct node* root,int key){
    while(root!=NULL){
        if(key==root->data){
            return root;
        }else if(key<root->data){
            root=root->left;
        }else{
            root=root->right;
        }
    }return NULL;
}
void insert(struct node* root,int key){
    struct node* prev=NULL;
    while(root!=NULL){
        prev=root;
        if(key==root->data){
            return;
        }else if (key < root->data){
            root=root->left;
        }else{
            root=root->right;
        }
    }
    struct node* new=createnode(key);
    if(key<prev->data){
        prev->left=new;
    }else{
         prev->right=new;
    }
}
// inorderPredecessor-left subtree ka rightmost child;
struct node* inorderPredecessor(struct node* root){
    root=root->left;
    while(root->left!=NULL){
        root=root->right;
    }return root;
}
struct node *deletenode(struct node *root,int val){
    struct node* iPre;
    if(root==NULL){
        return NULL;
    }if(root->left==NULL && root->right==NULL){
        free(root);
        return NULL;
    }

    if(val < root->data){
        root->left=deletenode(root->left,val);
    }
    else if(val > root->data){
        root->right=deletenode(root->right,val);
    }

    else{
        iPre=inorderPredecessor(root);
        root->data=iPre->data;
        root->left=deletenode(root->left,iPre->data);
    }return root;
}
int main(){
    struct node *p=createnode(1);// parent node
    struct node *p1=createnode(2);
    struct node *p2=createnode(3);
    struct node *p3=createnode(4);
    struct node *p4=createnode(5);
    struct node *p5=createnode(6);
    
    p->left=p1;
    p->right=p2;
    p1->left=p3;
    p1->right=p4;
    p2->left=p5;
    inorder(p);
    deletenode(p,3);
    printf("\n");
    inorder(p);

    insert(p,7);
    printf("\n%d\n",p->right->right->data);
    
    if(isBST(p)){
        printf("\nis a BST");
    }
    
    struct node* n=searchiter(p,6);
    if(n!=NULL){
        printf("\nFound: %d",n->data);
    }else{
        printf("elmnt not found");
    }
    return 0;
}