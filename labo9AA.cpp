#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

struct node
{
    int key;
    struct node *left, *right;
};

struct node *newNode(int item)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

void inorder(struct node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d \n", root->key);
        inorder(root->right);
    }
}

void preOrder(struct node *root)
{
    if (root == NULL)
        return;

    printf("%d \n", root->key);
    preOrder(root->left);
    preOrder(root->right);
}

struct node *insert(struct node *node, int key)
{
    /* If the tree is empty, return a new node */
    if (node == NULL)
        return newNode(key);
    /* Otherwise, recur down the tree */
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    /* return the (unchanged) node pointer */
    return node;
}

struct node *minValueNode(struct node *node)
{
    struct node *current = node;
    while (current && current->left != NULL)
        current = current->left;

    return current;
}

struct node *deleteNode(struct node *root, int key)
{
    // base case
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else
    {
        if (root->left == NULL)
        {
            struct node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct node *temp = root->left;
            free(root);
            return temp;
        }
        struct node *temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

void postOrder(struct node *root)
{
    if (root == NULL)
        return;

    // primero se recorre el lado izquierdo
    postOrder(root->left);

    // luego se recorre el lado derecho
    postOrder(root->right);

    // se imprime el valor del nodo.
    printf("%d \n", root->key);
}

struct node *lca(struct node *root, int n1, int n2)
{
    if (root == NULL)
    {
        return NULL;
    }
    // si ambos n1 y n2 son mas pequeños que root, lca ira a la izquierda
    if (root->key > n1 && root->key > n2)
    {
        return lca(root->left, n1, n2);
    }

    // si ambos n1 y n2 son mas pequeños que root, lca ira a la derecha
    if (root->key < n1 && root->key < n2)
    {
        return lca(root->right, n1, n2);
    }

    return root;
}

int findLevel(struct node *root, int k, int level)
{
    if (root == NULL)
    {
        return -1;
    }
    if (root->key == k)
    {
        return level;
    }

    int left = findLevel(root->left, k, level + 1);
    if (left == -1)
    {
        return findLevel(root->right, k, level + 1);
    }
    return left;
}

int findDistance(node *root, int a, int b)
{
    struct node *lca2 = lca(root, a, b);
    int d1 = findLevel(lca2, a, 0);
    int d2 = findLevel(lca2, b, 0);

    return d1 + d2;
}

int main()
{
    struct node *root = NULL;
    root = insert(root, 8);
    insert(root, 3);
    insert(root, 10);
    insert(root, 1);
    insert(root, 6);
    insert(root, 14);
    insert(root, 4);
    insert(root, 7);
    insert(root, 13);

    int n1 = 1, n2 = 13;
    int n3 = 1, n4 = 7;
    struct node *t = lca(root, n1, n2);
    printf("Primer ancestro de %d y %d es %d \n", n1, n2, t->key);
    std::cout << "Distancia entre " << n3 << " y " << n4 << " es: " << findDistance(root, n3, n4) << std::endl;

    return 0;
}