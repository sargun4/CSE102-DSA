#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node{
    long long data;
    long long height;
    struct node* left;
    struct node* right;
    
};
long long height(struct node* root){
    if (root == NULL)
        return 0;
    return root->height;
}
long long max(long long a, long long b){  
    return (a > b)? a : b;
}

struct node* createnode(long long data){
    struct node* temp=(struct node*)malloc(sizeof(struct node));
    temp->height=1;
    temp->data=data;
    temp->left=NULL;
    temp->right=NULL;
    return temp;
}
struct node* leftrotate(struct node* root){
    struct node* x=root->right;
    struct node* y=x->left;
    x->left=root;
    root->right=y;
    root->height=max(height(root->left),height(root->right)) + 1;
    x->height=max(height(x->left),height(x->right)) + 1;
    return x;
}
struct node* rightrotate(struct node* root){
    struct node* x=root->left;
    struct node* y=x->right;
    x->right=root;
    root->left=y;
    root->height=max(height(root->left),height(root->right)) + 1;
    x->height=max(height(x->left),height(x->right)) + 1;
    return x;
}

struct node* minvalnode(struct node* root){
    struct node* temp=root;
    while(temp->left!=NULL){
        temp=temp->left;
    }
    return temp;
}
struct node* maxvalnode(struct node* root){
    struct node* temp=root;
    while(temp->right!=NULL){
        temp=temp->right;
    }
    return temp;
}
long long balance_factor(struct node* root){
    if(root==NULL)
        return 0;
    return height(root->right)-height(root->left);
}

struct node* insert(struct node* root, long long x){
    if(root==NULL){
        return createnode(x);
    }
    if(x<(root->data)){
        root->left=insert(root->left,x);
    }
    else{
        root->right=insert(root->right,x);
    }
    root->height=1+max(height(root->right),height(root->left));
    long long BF=balance_factor(root);
    if(BF>1){
        if (balance_factor(root->right) >= 0) return leftrotate(root);
        else {root->right = rightrotate(root->right); return leftrotate(root);}
    }
    if(BF<-1){
        if (balance_factor(root->left)<= 0) return rightrotate(root);
        else{root->left = leftrotate(root->left); return rightrotate(root);}
    }
    return root;
}
struct node* delete(struct node* root, long long data){
    if (root == NULL) {
        return NULL;
    }
    if (root->data == data) {
        if (root->left == NULL) {
        struct node *temp = root->right;
        free(root);
        return temp;
        }
        else if (root->right == NULL) {
            struct node *temp = root->left;
            free(root);
            return temp;
        }
        else if (root->right != NULL && root->left != NULL) {
            struct node *min_node = minvalnode(root->right);
            root->data = min_node->data;
            root->right = delete(root->right, min_node->data);
        }
    }
    else if(data < root->data) {
        root->left = delete(root->left, data);
    }
    else{
        root->right = delete(root->right, data);
    }
    if(root==NULL){
        return root;
    }
    root->height=1+max(height(root->right),height(root->left));
    long long BF=balance_factor(root);
    if(BF>1){
        if (balance_factor(root->right) >= 0) return leftrotate(root);
        else {root->right = rightrotate(root->right); return leftrotate(root);}
    }
    if(BF<-1){
        if (balance_factor(root->left)<= 0) return rightrotate(root);
        else{root->left = leftrotate(root->left); return rightrotate(root);}
    }
    return root;
}


int main(){
    int N=0;
    scanf("%d",&N);
    long long sum=0;
    long long n=0;
    struct node* root=NULL;

    for(int i=0;i<N;i++){
        scanf("%lld",&n);
        root=insert(root,n);
        sum+=n;
    }
    for (int i = 0; i < N - 1; i++) {
        struct node* minnode = minvalnode(root);
        struct node* maxnode = maxvalnode(root);
        long long largest = maxnode->data;
        long long smallest = minnode->data;
        
        root = delete(root, largest);
        root = delete(root, smallest);
        
        long long diff = largest - smallest;
        sum += diff - (largest + smallest);
        
        root = insert(root, diff);
        printf("%lld\n", sum);
    }
    return 0;
}