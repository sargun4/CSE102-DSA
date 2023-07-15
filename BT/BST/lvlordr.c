void kthSmallest(struct Node* root, int k, int* count, int* result) {
    if (root != NULL) {
        kthSmallest(root->left, k, count, result);
        (*count)++;
        if (*count == k) {
            *result = root->data;
        }
        kthSmallest(root->right, k, count, result);
    }
}

int height(struct Node* root) {
    if (root == NULL) {
        return 0;
    } else {
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);
        if (leftHeight > rightHeight) {
            return leftHeight + 1;
        } else {
            return rightHeight + 1;
        }
    }
}

void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}
int size(struct Node* root) {
    if (root == NULL) {
        return 0;
    } else {
        return size(root->left) + 1 + size(root->right);
    }
}
struct Node* maxValueNode(struct Node* root) {
    struct Node* current = root;
    while (current->right != NULL) {
        current = current->right;
    }
    return current;
}
int countLeaves(struct Node* root) {
    if (root == NULL) {
        return 0;
    }
    if (root->left == NULL && root->right == NULL) {
        return 1;
    }
    return countLeaves(root->left) + countLeaves(root->right);
}
int isBalanced(struct Node* root) {
    int leftHeight, rightHeight;
    if (root == NULL) {
        return 1;
    }
    leftHeight = height(root->left);
    rightHeight = height(root->right);
    if (abs(leftHeight - rightHeight) <= 1 && isBalanced(root->left) && isBalanced(root->right)) {
        return 1;
    }
    return 0;
}
void printGivenLevel(struct Node* root, int level) {
    if (root == NULL) {
        return;
    }
    if (level == 1) {
        printf("%d ", root->data);
    } else if (level > 1) {
        printGivenLevel(root->left, level - 1);
        printGivenLevel(root->right, level - 1);
    }
}
// void printGivenLevel(struct Node* root, int level);
void printLevelOrder(struct Node* root) {
    int h = height(root);
    for (int i = 1; i <= h; i++) {
        printGivenLevel(root, i);
    }
}
struct Node* lca(struct Node* root, int n1, int n2){
    // struct Node* root;
    if (root == NULL)
        return NULL;
 
    // If both n1 and n2 are smaller than root, then LCA
    // lies in left
    if (root->data > n1 && root->data > n2)
        return lca(root->left, n1, n2);
 
    // If both n1 and n2 are greater than root, then LCA
    // lies in right
    if (root->data < n1 && root->data < n2)
        return lca(root->right, n1, n2);
    return root;
}

/* Compute the "maxDepth" of a tree -- the number of
    nodes along the longest path from the root node
    down to the farthest leaf node.*/
int maxDepth(struct node* node){
    if (node == NULL)
        return 0;
    else{
        int lDepth = maxDepth(node->left);
        int rDepth = maxDepth(node->right);
        if (lDepth > rDepth)
            return (lDepth + 1);
        else
            return (rDepth + 1);
    }
}
