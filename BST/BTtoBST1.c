// Create a temp array arr[] that stores inorder traversal of the tree. This step takes O(n) time.
// Sort the temp array arr[]. Time complexity of this step depends upon the sorting algorithm. In the following implementation, Quick Sort is used which takes (n^2) time. This can be done in O(nLogn) time using Heap Sort or Merge Sort.
// Again do inorder traversal of tree and copy array elements to tree nodes one by one. This step takes O(n) time.
#include <stdio.h>
#include <stdlib.h>
struct node {
    int data;
    struct node *left;
    struct node *right;
};
struct node* createnode(int data) {
    struct node* node = (struct node*) malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
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
void inorder(struct node* root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}
// input- BT, out-BST;
// s1=create inorder traversal of BT and save it in an arr;
// s2=sort arr;
// s3=copy sorted arr elmnts to tree(via inorder);
int countnodes(struct node* root){
    if(root==NULL) return 0;
    return 1+countnodes(root->left)+countnodes(root->right);
}
void arrtoBST(struct node*root,int *arr,int *iptr){
    if(root==NULL) return;
    //update left subtree
    arrtoBST(root->left,arr,iptr);
    //update roots data w arr data ,increment idx;
    root->data=arr[*iptr];
    (*iptr)++;
    //update right subtree
    arrtoBST(root->right,arr,iptr);
}
void inordertoArr(struct node* root,int * inorder,int *iptr){
    //to avoid i getting initialised(no local var), we need to pass i as ptr
    if(root==NULL) return;
    //recurse left subtree
    inordertoArr(root->left,inorder,iptr);
    //save to arr
    *(inorder+*iptr)=root->data;
    (*iptr)++;
    //recurse right subtree
    inordertoArr(root->right,inorder,iptr);
}

void BTtoBST(struct node* root){
    int n=0,i=0;//i- index
    int *arr=(int*)malloc(sizeof(int) * n); //arr of len n
   
    n=countnodes(root);
    inordertoArr(root,arr,&i);
    // sorting
    bubblesort(arr,n);
    i=0;// reset idx to 0.
    //copy arr elmnts back to bin tree
    arrtoBST(root,arr,&i);
    free(arr);
}    

void main(){
    struct node * root=createnode(10);
    root->left=createnode(40);
    root->right=createnode(25);
    root->right->right=createnode(15);
    root->left->left=createnode(30);
    printf("Inorder before\n");
    inorder(root);
    BTtoBST(root);
    printf("\nInorder after conversion\n");
    inorder(root);
}