#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    char key[10];
    struct node *left;
    struct node *right;
} node;

node *new_node(char *key)
{
    node *new = malloc(sizeof(node));
    strcpy(new->key, key);
    new->left = NULL;
    new->right = NULL;
    return new;
}

node *insert_node(node *root, char *key)
{
    if (root == NULL)
        return new_node(key);

    int cmp = strcmp(key, root->key);
    if (cmp < 0)
        root->left = insert_node(root->left, key);
    else if (cmp > 0)
        root->right = insert_node(root->right, key);

    return root;
}

void print_tree(node *root)
{
    if (root != NULL)
    {
        print_tree(root->left);
        printf("%s ", root->key);
        print_tree(root->right);
    }
}

int main()
{
    node *root = NULL;

    root = insert_node(root, "apple");
    root = insert_node(root, "banana");
    root = insert_node(root, "cherry");
    root = insert_node(root, "date");
    root = insert_node(root, "elderberry");

    print_tree(root);

    return 0;
}
