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

void inorder(struct node* root){
    if(root!=NULL){
        inorder(root->left);
        printf("%d ",root->data);
        inorder(root->right);
    } 
}

void merge(struct node* root1, struct node* root2, struct node** merged) {
    if (root1 == NULL && root2 == NULL) {
        return;
    }
    if (root1 == NULL) {
        *merged = root2;
        return;
    }
    if (root2 == NULL) {
        *merged = root1;
        return;
    }
    if (root1->data < root2->data) {
        *merged = root1;
        merge(root1->right, root2, &((*merged)->right));
    } else {
        *merged = root2;
        merge(root1, root2->right, &((*merged)->right));
    }
}

int countNodes(struct node* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + countNodes(root->left) + countNodes(root->right);
}

float findMedian(struct node* root) {
    int n = countNodes(root);
    if (n % 2 == 0) {
        struct node* ptr1 = root, *ptr2 = root;
        for (int i = 0; i < n/2 - 1; i++) {
            ptr2 = ptr2->right;
        }
        ptr1 = ptr2->right;
        return (float)(ptr1->data + ptr2->data) / 2.0;
    } else {
        struct node* ptr = root;
        for (int i = 0; i < n/2; i++) {
            ptr = ptr->right;
        }
        return (float)ptr->data;
    }
}

float findMean(struct node* root) {
    int sum = 0, count = 0;
    if (root == NULL) {
        return 0;
    }
    struct node* stack[100];
    int top = -1;
    struct node* curr = root;
    while (curr != NULL || top != -1) {
        while (curr != NULL) {
            stack[++top] = curr;
            curr = curr->left;
        }
        curr = stack[top--];
        sum += curr->data;
        count++;
        curr = curr->right;
    }
    return (float)sum / (float)count;
}
int main() {
    struct node *root1 = NULL, *root2 = NULL;
    root1 = insert(root1, 50);
    root1 = insert(root1, 30);
    root1 = insert(root1, 20);
    root1 = insert(root1, 40);
    root1 = insert(root1, 70);
    root1 = insert(root1, 60);
    root1 = insert(root1, 80);
    printf("Inorder traversal of tree 1: ");
    inorder(root1);
    printf("\n");

    root2 = insert(root2, 45);
    root2 = insert(root2, 35);
    root2 = insert(root2, 25);
    root2 = insert(root2, 65);
    root2 = insert(root2, 75);
    printf("Inorder traversal of tree 2: ");
    inorder(root2);
    printf("\n");

    // struct node *mergedRoot = merge(root1, root2);
    // printf("Inorder traversal of merged tree: ");
    // inorder(mergedRoot);
    // printf("\n");

    double mean = findMean(root1);
    printf("Mean of the values in the merged tree: %.2lf\n", mean);

    double median = findMedian(root2);
    printf("Median of the values in the merged tree: %.2lf\n", median);

    return 0;
}
