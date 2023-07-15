struct Tree* QuickSearch(struct Tree* root, int key, int* depth) {
    if (root == NULL) {
        *depth = 0;
        return NULL;
    }
    if (key == root->val) {
        return root;
    }
    if (key < root->val) {
        struct Tree* left = QuickSearch(root->left, key, depth);
        if (left != NULL) {
            if (left->right != NULL) {
                root->left = left->right;
                left->right = root;
            }
            return left;
        }
        else {
            (*depth)++;
            return root;
        }
    }
    else {
        struct Tree* right = QuickSearch(root->right, key, depth);
        if (right != NULL) {
            if (right->left != NULL) {
                root->right = right->left;
                right->left = root;
            }
            return right;
        }
        else {
            (*depth)++;
            return root;
        }
    }
}
