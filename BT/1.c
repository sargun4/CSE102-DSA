#include <stdio.h>
#include <stdlib.h>
struct node {
	int data;
	struct node *left, *right;
};
void printCurrentLevel(struct node* root, int level){
	if (root == NULL)
		return;
	if (level == 1)
		printf("%d ", root->data);
	else if (level > 1) {
		printCurrentLevel(root->left, level - 1);
		printCurrentLevel(root->right, level - 1);
	}
}
int height(struct node* node){
	if (node == NULL)
		return 0;
	else {
		int lheight = height(node->left);
		int rheight = height(node->right);
		if (lheight > rheight)
			return (lheight + 1);
		else
			return (rheight + 1);
	}
}
// Time Complexity: O(N2), where N is the number of nodes in the skewed tree. So time complexity of printLevelOrder() is O(n) + O(n-1) + O(n-2) + .. + O(1) which is O(N2). 
void printLevelOrder(struct node* root){
	int h = height(root);
	int i;
	for (i = 1; i <= h; i++)
		printCurrentLevel(root, i);
}
struct node* create(int data){
    struct node* node = (struct node*)malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return(node);
}

void inorder(struct node* root){
    if (root != NULL){
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

struct node* insert(struct node* node, int data){
    if (node == NULL) return create(data);

    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);

    return node;
}

struct node* minValueNode(struct node* node){
    struct node* current = node;
    while (current && current->left != NULL)
        current = current->left;

    return current;
}

struct node* maxValueNode(struct node* node){
    struct node* current = node;
    while (current && current->right != NULL)
        current = current->right;

    return current;
}

struct node* inorderSuccessor(struct node* root, struct node* n){
    if (n->right != NULL)
        return minValueNode(n->right);

    struct node* succ = NULL;
    while (root != NULL){
        if (n->data < root->data){
            succ = root;
            root = root->left;
        }
        else if (n->data > root->data)
            root = root->right;
        else
            break;
    }

    return succ;
}

struct node* inorderPredecessor(struct node* root, struct node* n){
    if (n->left != NULL)
        return maxValueNode(n->left);

    struct node* pred = NULL;
    while (root != NULL){
        if (n->data > root->data){
            pred = root;
            root = root->right;
        }
        else if (n->data < root->data)
            root = root->left;
        else
            break;
    }

    return pred;
}
int count(struct node* root){
    if(root==NULL) return 0;
    return 1+count(root->left)+count(root->right);
}
int kthSmallest(struct node* root, int k){
    if (root == NULL)
        return -1;

    int left_count = 0;
    if (root->left != NULL)
        left_count = count(root->left);

    if (k <= left_count)
        return kthSmallest(root->left, k);
    else if (k == left_count + 1)
        return root->data;
    else
        return kthSmallest(root->right, k - left_count - 1);
}

int kthLargest(struct node* root, int k){
    if (root == NULL)
        return -1;

    int right_count = 0;
    if (root->right != NULL)
        right_count = count(root->right);

    if (k <= right_count)
        return kthLargest(root->right, k);
    else if (k == right_count + 1)
        return root->data;
    else
        return kthLargest(root->left, k - right_count - 1);
}

void storeInorder(struct node* root, int* arr, int* idx){
    if (root != NULL){
        storeInorder(root->left, arr, idx);
        arr[(*idx)++] = root->data;
        storeInorder(root->right, arr, idx);
    }
}
int getMedian(struct node* root){
    int ctr = count(root);
    int arr[ctr], i = 0;
    storeInorder(root, arr, &i);
    if (ctr % 2 == 0) {
        return (arr[ctr/2 - 1] + arr[ctr/2]) / 2;
    }
    else {
        return arr[ctr/2];
    }
}

int hasPairWithSum(struct node* root, int sum){
    int arr[count(root)];
    int idx = 0;
    storeInorder(root, arr, &idx);

    int i = 0, j = idx - 1;
    while (i < j){
        int curr_sum = arr[i] + arr[j];
        if (curr_sum == sum)
            return 1;
        else if (curr_sum < sum)
            i++;
        else
            j--;
    }

    return 0;
}

int main(){
    struct node* root = NULL;
    int n, data, k, sum;
    printf("Enter number of nodes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter node %d: ", i + 1);
        scanf("%d", &data);
        root = insert(root, data);
    }

    printf("Inorder traversal: ");
    inorder(root);
    printf("\n");

    printf("Enter a value of k to find the kth smallest element: ");
    scanf("%d", &k);
    printf("The %dth smallest element is: %d\n", k, kthSmallest(root, k));

    printf("Enter a value of k to find the kth largest element: ");
    scanf("%d", &k);
    printf("The %dth largest element is: %d\n", k, kthLargest(root, k));

    printf("The median element is: %d\n", getMedian(root));

    printf("Enter a sum: ");
    scanf("%d", &sum);
    if (hasPairWithSum(root, sum))
        printf("There exists a pair with the given sum.\n");
    else
        printf("No such pair exists.\n");

    printf("Level Order traversal of binary tree is \n");
	printLevelOrder(root);
	 
    return 0;
}