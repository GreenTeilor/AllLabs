#include <stdlib.h>
#include <stdio.h>

typedef struct Tree
{
    int info;
    Tree* left;
    Tree* right;
} *TTree;

void push(TTree* tree, const int value)
{
    if (*tree == NULL)
    {
        *tree = (TTree)malloc(sizeof(Tree));
        (*tree)->info = value;
        (*tree)->left = NULL;
        (*tree)->right = NULL;
    }
    else
    {
        //Condition have to be opposite: (value > (*tree)->info), but due to output that print tree 
        //in mirror order, search binary tree is built in mirror order
        if (value < (*tree)->info)
            push(&(*tree)->right, value);
        else
            push(&(*tree)->left, value);
    }
}

void print_Tree(const int level, const TTree tree)
{
    if (tree)
    {
        print(level + 1, tree->left);
        for (int i = 0; i < level; i++)
            printf("  ");
        printf(">%d", tree->info);
        printf("\n");
        print(level + 1, tree->right);
    }
}

//Function return number of nodes with two links
int count(const TTree tree)
{
    static int num = 0;
    if (tree)
    {
        if (tree->left && tree->right)
            ++num;
        if (tree->left)
            count(tree->left);
        if (tree->right)
            count(tree->right);
    }
    return num;
}

int main()
{
    TTree tree = NULL;
    int isExit = 0;
    int option;
    while (!isExit)
    {
        printf("Input option: ");
        scanf_s("%d", &option);
        switch (option)
        {
        case 1:
            printf("Input value to push: ");
            int value;
            scanf_s("%d", &value);
            push(&tree, value);
            break;
        case 2:
            printf("Your tree:\n");
            print(0, tree);
            break;
        case 3:
            printf("Number of nodes with two links: %d\n", count(tree));
            break;
        default:
            isExit = 1;
        }
    }
}
