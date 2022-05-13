#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int cost(int **mat)
{
    int cost = 0;

    int *row_tmp = malloc(sizeof(int) * size);
    int *col_tmp = malloc(sizeof(int) * size);

    for (int i = 0; i < size; i++)
    {
        row_tmp[i] = INT_MAX;
        col_tmp[i] = INT_MAX;
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (mat[i][j] < row_tmp[i])
                row_tmp[i] = mat[i][j];
        }
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (mat[i][j] != INT_MAX && row_tmp[i] != INT_MAX)
                mat[i][j] -= row_tmp[i];
        }
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (mat[i][j] < col_tmp[j])
                col_tmp[j] = mat[i][j];
        }
    }
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (mat[i][j] != INT_MAX && col_tmp[j] != INT_MAX)
                mat[i][j] -= col_tmp[j];
        }
    }
    for (int i = 0; i < size; i++)
    {
        if (row_tmp[i] != INT_MAX)
            cost += row_tmp[i];
        if (col_tmp[i] != INT_MAX)
            cost += col_tmp[i];
    }
    // printf("Cost = %d\n", cost);

    return cost;
}

void printpath(int *path)
{
    printf("Path = \n");

    for (int i = 0; i < size; i++)
        printf("%d ", path[i]);

    printf("\n");
}

void createnode(struct Node_s *root, struct Node_s *node, int **mat, int *path, int lvl, int rowdiag, int coldiag, int cost_v)
{

    node->mat = malloc(sizeof(int *) * size);

    for (int i = 0; i < size; i++)
    {
        node->mat[i] = malloc(sizeof(int) * size);
        for (int j = 0; j < size; j++)
            node->mat[i][j] = mat[i][j];
    }
    node->path = malloc(sizeof(int) * size);

    for (int i = 0; i < size; i++)
        node->path[i] = path[i];

    if (lvl)
    {
        printf("%d -> %d\n", rowdiag, coldiag);
        node->path[lvl] = coldiag;
        for (int i = 0; i < size; i++)
        {
            node->mat[rowdiag][i] = INT_MAX;
            node->mat[i][coldiag] = INT_MAX;
        }
        //  node->path[lvl] = size * rowdiag + coldiag;
    }

    node->mat[coldiag][0] = INT_MAX;

    node->level = lvl;

    node->left = node->right = node->up = NULL;

    node->coldiag = coldiag;

    node->cost = cost_v + cost(node->mat);

    if (root != node)
    {
        if (node->cost < root->cost)
        {
            root->left = insert((root)->left, node);
        }
        else if (node->cost >= root->cost)
        {
            root->right = insert((root)->right, node);
        }
    }
    else
        root = node;
}

struct Node_s *insert(struct Node_s *tree, struct Node_s *node)
{
    if (tree == NULL)
    {
        return node;
    }

    if (node->cost < tree->cost)
    {
        tree->left = insert((tree)->left, node);
    }
    else
    {
        tree->right = insert((tree)->right, node);
    }

    return tree;
}

struct Node_s *searchmin(struct Node_s *node)
{
    struct Node_s *curr = node;

    while (curr && curr->left != NULL)
        curr = curr->left;

    return curr;
}

/*struct Node_s *searchmin(struct Node_s *node)
{
    if (node == NULL)
        return node;

    struct Node_s *res = node;

    if (node->left != NULL)
    {
        struct Node_s *min_left = searchmin(node->left);
        if (min_left->cost > res->cost)
            res = min_left;
    }

    if (node->right != NULL)
    {
        struct Node_s *min_right = searchmin(node->right);

        if (min_right->cost > res->cost)
            res = min_right;
    }
    return res;
}*/

void inorder(struct Node_s *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->cost);
        inorder(root->right);
    }
}

struct Node_s *deletenode(struct Node_s *root, struct Node_s *node)
{

    if (root == NULL)
        return root;
    else if (node == root)
    {
        if (root->left == NULL)
        {
            struct Node_s *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct Node_s *temp = root->left;
            free(root);
            return temp;
        }
        struct Node_s *temp = searchmin(root->right);
        root->cost = temp->cost;
        root->right = deletenode(root->right, temp);
    }
    else if (node->cost < root->cost)
    {
        root->left = deletenode(root->left, node);
    }
    else if (node->cost >= root->cost)
        root->right = deletenode(root->right, node);

    return root;
}

int resolve(int **mat)
{
    int *path = malloc(sizeof(int) * size);

    struct Node_s *root;
    root = malloc(sizeof(struct Node_s));

    createnode(root, root, mat, path, 0, 0, 0, 0);

    while (root != NULL)
    {
        struct Node_s *min;
        min = searchmin(root);
        printf("Min = %d %d\n", min->cost, min->level);
        int i = min->coldiag;

        if (min->level == size - 1)
        {
            //min->path[i] = 0;
            printpath(min->path);
            return min->cost;
        }
        // printpath(min->path);

        // return 10;

        for (int j = 0; j < size; j++)
        {
            if (min->mat[i][j] != INT_MAX)
            {
                printf("i  = %d j = %d  lvl = %d\n", i, j, min->level + 1);
                struct Node_s *node;
                node = malloc(sizeof(struct Node_s));
                createnode(root, node, min->mat, min->path, min->level + 1, i, j, (min->cost + min->mat[i][j]));
                //  printpath(node->path);
                // printf("Cost = %d %d\n", node->cost, node->level);
                // node->cost = min->cost + min->mat[i][j] + cost(node->mat);

                // printf("Order\n");
                // inorder(root);
            }
        }
        root = deletenode(root, min);
    }

    return INT_MAX;
}

int main()
{
  

    return 0;
}