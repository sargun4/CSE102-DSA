#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    int data;
    struct node* left;
    struct node* right;
} node;
// Structure for queue node
struct QueueNode {
    struct node* data;
    struct QueueNode* next;
};

// Structure for queue
struct Queue {
    struct QueueNode* front;
    struct QueueNode* rear;
};

// Function to create a new queue node
struct QueueNode* newQueueNode(struct node* data) {
    struct QueueNode* node = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    node->data = data;
    node->next = NULL;
    return node;
}

// Function to create an empty queue
struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

// Function to check if the queue is empty
int isQueueEmpty(struct Queue* queue) {
    return (queue->front == NULL);
}

// Function to add a node to the queue
void enqueue(struct Queue* queue, struct node* data) {
    struct QueueNode* node = newQueueNode(data);
    if (queue->rear == NULL) {
        queue->front = node;
        queue->rear = node;
    } else {
        queue->rear->next = node;
        queue->rear = node;
    }
}

// Function to remove a node from the queue
struct node* dequeue(struct Queue* queue) {
    if (isQueueEmpty(queue)) {
        return NULL;
    }
    struct QueueNode* temp = queue->front;
    struct node* data = temp->data;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return data;
}

node* newNode(int key) {
    node* temp = (node*) malloc(sizeof(node));
    temp->data = key;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}
node* insert(node* root, int key) {
    if (root == NULL) {
        return newNode(key);
    }
    if (key < root->data) {
        root->left = insert(root->left, key);
    }
    else if (key > root->data) {
        root->right = insert(root->right, key);
    }
    return root;
}

// smallest value node in the BST
node* minValueNode(node* root) {
    node* current = root;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}
// Function to find the maximum depth of a binary tree
int maxDepth(node* root) {
    if (root == NULL) {
        return 0;
    }
    int leftDepth = maxDepth(root->left);
    int rightDepth = maxDepth(root->right);
    return 1 + ((leftDepth > rightDepth) ? leftDepth : rightDepth);
}
// Function to check if there exists a root-to-leaf path whose sum equals the given sum
int hasPathSum(node* root, int sum) {
    if (root == NULL) {
        return 0;
    }
    if (root->left == NULL && root->right == NULL) {
        return (sum == root->data);
    }
    return hasPathSum(root->left, sum - root->data) || hasPathSum(root->right, sum - root->data);
}

// Function to find the diameter of a binary tree
int diameter(node* root) {
    if (root == NULL) {
        return 0;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    int leftDiameter = diameter(root->left);
    int rightDiameter = diameter(root->right);
    return ((leftHeight + rightHeight > leftDiameter) ? leftHeight + rightHeight : leftDiameter > rightDiameter) ? leftDiameter : rightDiameter;
}

// Function to find the height of a binary tree
int height(node* root) {
    if (root == NULL) {
        return 0;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return 1 + ((leftHeight > rightHeight) ? leftHeight : rightHeight);
}


// Function to traverse a binary tree in spiral order
// takes O(n) time complexity and O(n) space complexity since we use a queue to store the nodes
void spiralTraversal(struct node* root) {
    if (root == NULL) {
        return;
    }
    struct Queue* q = createQueue();
    enqueue(q, root);
    int level = 1;
    while (!isQueueEmpty(q)) {
        int size = 0;
        while (!isQueueEmpty(q) && size < level) {
            struct node* curr = dequeue(q);
            printf("%d ", curr->data);
            if (curr->left != NULL) {
                enqueue(q, curr->left);
            }
            if (curr->right != NULL) {
                enqueue(q, curr->right);
            }
            size++;
        }
        level++;
        printf("\n");
        if (!isQueueEmpty(q)) {
            size = 0;
            struct QueueNode* temp = q->front;
            while (temp != NULL && size < level) {
                printf("%d ", temp->data->data);
                temp = temp->next;
                size++;
            }
            level++;
            printf("\n");
        }
    }
}

node* delete(node* root, int key) {
    if (root == NULL) {
        return root;
    }
    if (key < root->data) {
        root->left = delete(root->left, key);
    }
    else if (key > root->data) {
        root->right = delete(root->right, key);
    }
    else {
        if (root->left == NULL) {
            node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            node* temp = root->left;
            free(root);
            return temp;
        }
        node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = delete(root->right, temp->data);
    }
    return root;
}
void inorder(node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}
node* maxValueNode(node* root) {
    node* current = root;
    while (current->right != NULL) {
        current = current->right;
    }
    return current;
}
// Function to check if a given key is present in the BST
int contains(node* root, int key) {
    if (root == NULL) {
        return 0;
    }
    if (root->data == key) {
        return 1;
    }
    if (key < root->data) {
        return contains(root->left, key);
    }
    return contains(root->right, key);
}

// Function to find the inorder successor of a node with a given key in the BST
node* successor(node* root, int key) {
    node* current = search(root, key);
    if (current == NULL) {
        return NULL;
    }
    if (current->right != NULL) {
        return minValueNode(current->right);
    }
    node* successor = NULL;
    node* ancestor = root;
    while (ancestor != current) {
        if (current->data < ancestor->data) {
            successor = ancestor;
            ancestor = ancestor->left;
        }
        else {
            ancestor = ancestor->right;
        }
    }
    return successor;
}

// Function to find the inorder predecessor of a node with a given key in the BST
node* predecessor(node* root, int key) {
    node* current = search(root, key);
    if (current == NULL) {
        return NULL;
    }
    if (current->left != NULL) {
        return maxValueNode(current->left);
    }
    node* predecessor = NULL;
    node* ancestor = root;
    while (ancestor != current) {
        if (current->data > ancestor->data) {
            predecessor = ancestor;
            ancestor = ancestor->right;
        }
        else {
            ancestor = ancestor->left;
        }
    }
    return predecessor;
}

// Function to print the BST in level order traversal (i.e., BFS)
void levelOrder(node* root) {
    if (root == NULL) {
        return;
    }
    struct queue* q = createQueue();
    enqueue(q, root);
    while (!isEmpty(q)) {
        node* current = dequeue(q);
        printf("%d ", current->data);
        if (current->left != NULL) {
            enqueue(q, current->left);
        }
        if (current->right != NULL) {
            enqueue(q, current->right);
        }
    }
    deleteQueue(q);
}

// Function to check if a given binary tree is a valid BST
int isValidBST(node* root, int min, int max) {
    if (root == NULL) {
        return 1;
    }
    if (root->data < min || root->data > max) {
        return 0;
    }
    return isValidBST(root->left, min, root->data - 1) && isValidBST(root->right, root->data + 1, max);
}

// Function to delete the entire BST
void deleteBST(node* root) {
    if (root == NULL) {
        return;
    }
    deleteBST(root->left);
    deleteBST(root->right);
    free(root);
}
// Function to find the k-th smallest element in the BST
int kthSmallest(node* root, int k) {
    if (root == NULL) {
        return -1;
    }
    int count = size(root->left);
    if (k <= count) {
        return kthSmallest(root->left, k);
    }
    else if (k == count + 1) {
        return root->data;
    }
    else {
        return kthSmallest(root->right, k - count - 1);
    }
}

// Function to find the LCA (Lowest Common Ancestor) of two nodes with given keys in the BST
node* LCA(node* root, int key1, int key2) {
    if (root == NULL) {
        return NULL;
    }
    if (root->data > key1 && root->data > key2) {
        return LCA(root->left, key1, key2);
    }
    else if (root->data < key1 && root->data < key2) {
        return LCA(root->right, key1, key2);
    }
    else {
        return root;
    }
}

// Function to find the distance between two nodes with given keys in the BST
int distance(node* root, int key1, int key2) {
    node* lca = LCA(root, key1, key2);
    int dist1 = findLevel(lca, key1, 0);
    int dist2 = findLevel(lca, key2, 0);
    return dist1 + dist2;
}

// Helper function to find the level of a given key in the BST
int findLevel(node* root, int key, int level) {
    if (root == NULL) {
        return -1;
    }
    if (root->data == key) {
        return level;
    }
    int leftLevel = findLevel(root->left, key, level + 1);
    if (leftLevel != -1) {
        return leftLevel;
    }
    return findLevel(root->right, key, level + 1);
}
// Function to count the number of nodes in the BST that are in the range [low, high]
int countInRange(node* root, int low, int high) {
    if (root == NULL) {
        return 0;
    }
    if (root->data >= low && root->data <= high) {
        return 1 + countInRange(root->left, low, high) + countInRange(root->right, low, high);
    }
    else if (root->data < low) {
        return countInRange(root->right, low, high);
    }
    else {
        return countInRange(root->left, low, high);
    }
}

// Function to find the inorder successor of a node with a given key in the BST
node* inorderSuccessor(node* root, int key) {
    if (root == NULL) {
        return NULL;
    }
    node* successor = NULL;
    while (root != NULL) {
        if (root->data > key) {
            successor = root;
            root = root->left;
        }
        else {
            root = root->right;
        }
    }
    return successor;
}

// Function to find the inorder predecessor of a node with a given key in the BST
node* inorderPredecessor(node* root, int key) {
    if (root == NULL) {
        return NULL;
    }
    node* predecessor = NULL;
    while (root != NULL) {
        if (root->data < key) {
            predecessor = root;
            root = root->right;
        }
        else {
            root = root->left;
        }
    }
    return predecessor;
}

// Function to find the largest BST in a given binary tree
int largestBST(node* root) {
    int min = INT_MIN, max = INT_MAX;
    return largestBSTUtil(root, &min, &max);
}

// Helper function to find the largest BST in a given binary tree
int largestBSTUtil(node* root, int* min, int* max) {
    if (root == NULL) {
        return 0;
    }
    int leftFlag = 0, rightFlag = 0, leftSize = 0, rightSize = 0;
    int currMin = INT_MAX, currMax = INT_MIN;
    if (root->left == NULL && root->right == NULL) {
        *min = root->data;
        *max = root->data;
        return 1;
    }
    if (root->left != NULL) {
        leftSize = largestBSTUtil(root->left, min, max);
        if (leftSize && root->data > *max) {
            leftFlag = 1;
        }
        currMin = *min;
    }
    else {
        currMin = root->data;
        leftFlag = 1;
    }
    if (root->right != NULL) {
        rightSize = largestBSTUtil(root->right, min, max);
        if (rightSize && root->data < *min) {
            rightFlag = 1;
        }
        currMax = *max;
    }
    else {
        currMax = root->data;
        rightFlag = 1;
    }
    if (leftFlag && rightFlag) {
        if (root->data > *max) {
            *max = root->data;
        }
        if (root->data < *min) {
            *min = root->data;
        }
        return 1 + leftSize + rightSize;
    }
    else {
        return fmax(leftSize, rightSize);
    }
}

// Helper function to find the node with the minimum value in the BST
node* minValueNode(node* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

// Function to check if two BSTs are identical or not
int isIdentical(node* root1, node* root2) {
    if (root1 == NULL && root2 == NULL) {
        return 1;
    }
    if (root1 == NULL || root2 == NULL) {
        return 0;
    }
    if (root1->data == root2->data) {
        return isIdentical(root1->left, root2->left) && isIdentical(root1->right, root2->right);
    }
    else {
        return 0;
    }
}

// Function to check if a given binary tree is a BST or not
int isBST(node* root) {
    return isBSTUtil(root, INT_MIN, INT_MAX);
}

// Helper function to check if a given binary tree is a BST or not
int isBSTUtil(node* root, int min, int max) {
    if (root == NULL) {
        return 1;
    }
    if (root->data < min || root->data > max) {
        return 0;
    }
    return isBSTUtil(root->left, min, root->data - 1) && isBSTUtil(root->right, root->data + 1, max);
}

int main() {
    node* root = NULL;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    printf("Inorder traversal of the BST: ");
    inorder(root);

    printf("\nDelete 20\n");
    root = delete(root, 20);
    printf("Inorder traversal of the modified BST: ");
    inorder(root);

    printf("\nDelete 30\n");
    root = delete(root, 30);
    printf("Inorder traversal of the modified BST: ");
    inorder(root);

    // printf("\nDelete 
    return 0;
}
// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>
// struct node {
//     int data;
//     struct node *left;
//     struct node *right;
// };

// struct node *createNode(int data) {
//     struct node *newNode = (struct node*) malloc(sizeof(struct node));
//     newNode->data = data;
//     newNode->left = NULL;
//     newNode->right = NULL;
//     return newNode;
// }

// void levelOrder(struct node *root) {
//     if (root == NULL) {
//         return;
//     }

//     struct node *queue[100];
//     int front = 0, rear = 0;
//     queue[rear++] = root;

//     while (front < rear) {
//         struct node *current = queue[front++];
//         printf("%d ", current->data);

//         if (current->left != NULL) {
//             queue[rear++] = current->left;
//         }
//         if (current->right != NULL) {
//             queue[rear++] = current->right;
//         }
//     }
// }
// void inorder(struct node *root){
//     if(root!=NULL){
//         inorder(root->left);
//         printf("%d ",root->data);
//         inorder(root->right);
//     }
// }
// int maxDepth(struct node* node){
//     if (node == NULL) return 0;
//     else {
//         /* compute the depth of each subtree */
//         int lDepth = maxDepth(node->left);
//         int rDepth = maxDepth(node->right);
//         /* use the larger one */
//         if (lDepth > rDepth)
//             return (lDepth + 1);
//         else
//             return (rDepth + 1);
// }}
// int main() {
//     struct node *root = createNode(1);
//     root->left = createNode(2);
//     root->right = createNode(3);
//     root->left->left = createNode(4);
//     root->left->right = createNode(5);
//     printf("Level order traversal: ");
//     levelOrder(root);
//     printf("\n");
//     inorder(root);
//     printf(maxDepth(root));
//     return 0;
// }
