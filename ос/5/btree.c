#include "btree.h"

void TreeInsert(BTREE *root, ElemType* newKey)
{
    if (!(*root)) {
        BTREE newNode = (BTREE) malloc(sizeof(*newNode));
        if (!newNode) {
            printf("Error: no memory\n");
            exit(FAILURE);
        }

        newNode->left = newNode->right = NULL;
        strcpy(newNode->key, newKey);
        *root = newNode;

        return;
    }

    if (strcmp(newKey, (*root)->key) <= 0) {
        TreeInsert(&(*root)->left, newKey);
    } else {
        TreeInsert(&(*root)->right, newKey);
    }
}

BTREE TreeFind(BTREE root, ElemType* key)
{
    if (!root) {
        return root;
    }

    if (strcmp(key, root->key) < 0) {
        return TreeFind(root->left, key);
    } else if (strcmp(key, root->key) > 0) {
        return TreeFind(root->right, key);
    } else {
        return root;
    }
}

BTREE minValueNode(BTREE root)
{
    BTREE cur = root;
    while (cur->left)
        cur = cur->left;
    return cur;
}

BTREE TreeRemove(BTREE root, ElemType* key)
{
    if (!root)
        return root;

    if (strcmp(key, root->key) < 0) {
        root->left = TreeRemove(root->left, key);
    } else if (strcmp(key, root->key) > 0) {
        root->right = TreeRemove(root->right, key);
    } else {
        if (!root->left) {
            BTREE tmp = root->right;
            free(root);
            root = NULL;
            return tmp;
        } else if (!root->right) {
            BTREE tmp = root->left;
            free(root);
            root = NULL;
            return tmp;
        }

        BTREE tmp = minValueNode(root->right);
        strcpy(root->key, tmp->key);
        root->right = TreeRemove(root->right, tmp->key);
    }
    return root;
}

void TreeNodePrint(BTREE node, int idx)
{
    if (node) {
        TreeNodePrint(node->left, idx + 1);
        for (int j = 0; j < idx; ++j)
            putchar('\t');
        printf("%s\n", node->key);
        TreeNodePrint(node->right, idx + 1);
    }
}

void TreePrint(BTREE root)
{
    if (root) {
        TreeNodePrint(root, 0);
    } else {
        printf("Tree is empty\n");
    }
}

void TreeDestroy(BTREE root)
{
    if (root) {
        TreeDestroy(root->right);
        TreeDestroy(root->left);
    }
    free(root);
    root = NULL;
}

bool TreeIsEmpty(BTREE root)
{
    return !root;
}
