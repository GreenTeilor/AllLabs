#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stack>

static const int BUFFER_SIZE = 256;

struct Stack
{
    int top;
    char arr[1000];
};

struct Node 
{
    char m_info;
    Node* leftNode;
    Node* rightNode;
} ;

typedef Node* Tree;

void initNode(Tree currentNode, char info, Tree leftNode, Tree rightNode)
{
    currentNode->m_info = info;
    currentNode->leftNode = leftNode;
    currentNode->rightNode = rightNode;
}

void initNode(Tree currentNode, char info)
{
    currentNode->m_info = info;
    currentNode->leftNode = NULL;
    currentNode->rightNode = NULL;
}

void initStack(Stack* stack)
{
    stack->top = -1;
}

void push(Stack* stack, char value)
{
    ++(stack->top);
    stack->arr[stack->top] = value;
}

char pop(Stack* stack)
{
    char temp  = stack->arr[stack->top];
    --(stack->top);
    return temp;
}

bool isEmpty(Stack* stack)
{
    return stack->top == -1;
}

char top(Stack* stack)
{
    return stack->arr[stack->top];
}

int relPriority(char symb)
{
    if (symb == '+' || symb == '-')
        return 1;
    if (symb == '*' || symb == '/')
        return 3;
    if (symb == '^')
        return 6;
    if (symb >= 'a' && symb <= 'z')
        return 7;
    if (symb == '(')
        return 9;
    if (symb == ')')
        return 0;
    else
        return -1;
}

int stackPriority(char symb)
{
    if (symb == '+' || symb == '-')
        return 2;
    if (symb == '*' || symb == '/')
        return 4;
    if (symb == '^')
        return 5;
    if (symb >= 'a' && symb <= 'z')
        return 8;
    if (symb == '(')
        return 0;
    if (symb == ')')
        return -1;
    else
        return -1;
}

void revPolandExpression(char* expression, char* revPolExpr)
{
    Stack stack;
    initStack(&stack);

    //Reverse poland expression
    int i = 0;
    while (expression[i])
    {
        if (isEmpty(&stack) || (relPriority(expression[i]) > stackPriority(top(&stack))))
            push(&stack, expression[i]);
        else
        {
            if (expression[i] == ')')
            {
                while (top(&stack) != '(')
                {
                    char temp = pop(&stack);
                    char symbStr[2];
                    symbStr[1] = '\0';
                    symbStr[0] = temp;
                    strcat_s(revPolExpr, BUFFER_SIZE, symbStr);
                }
                pop(&stack);
            }
            else
            {
                while (!isEmpty(&stack) && (relPriority(expression[i]) < stackPriority(top(&stack))))
                {
                    char temp = pop(&stack);
                    char symbStr[2];
                    symbStr[1] = '\0';
                    symbStr[0] = temp;
                    strcat_s(revPolExpr, BUFFER_SIZE, symbStr);
                }

                push(&stack, expression[i]);
            }
        }
        ++i;
    }

    //Pop all whats left in stake
    while (!isEmpty(&stack))
    {
        char temp = pop(&stack);
        char symbStr[2];
        symbStr[1] = '\0';
        symbStr[0] = temp;
        strcat_s(revPolExpr, BUFFER_SIZE, symbStr);
    }
}

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

Tree buildTree(char* postfix)
{
    if (strlen(postfix) == 0) {
        return nullptr;
    }

    std::stack<Tree> s;

    int i = 0;
    while(postfix[i])
    {
        if (isOperator(postfix[i]))
        {
            Tree x = s.top();
            s.pop();

            Tree y = s.top();
            s.pop();

            Tree tree = new Node;
            initNode(tree, postfix[i], y, x);

            s.push(tree);
        }

        else {
            Tree tree = new Node;
            initNode(tree, postfix[i]);
            s.push(tree);
        }
        ++i;
    }

    return s.top();
}

void pref(Tree tree)
{
    if (tree == nullptr) {
        return;
    }
    printf("%c", tree->m_info);
    pref(tree->leftNode);
    pref(tree->rightNode);
}

void inf(Tree tree)
{
    if (tree == nullptr) {
        return;
    }

    if (isOperator(tree->m_info)) {
        printf("(");
    }

    inf(tree->leftNode);
    printf("%c", tree->m_info);
    inf(tree->rightNode);

    if (isOperator(tree->m_info)) {
        printf(")");
    }
}

void post(Tree tree)
{
    if (tree == nullptr) {
        return;
    }
    post(tree->leftNode);
    post(tree->rightNode);
    printf("%c", tree->m_info);
}

void print_Tree(const int level, const Tree tree)
{
    if (tree)
    {
        print_Tree(level + 1, tree->rightNode);
        for (int i = 0; i < level; i++)
            printf("  ");
        printf(">%c", tree->m_info);
        printf("\n");
        print_Tree(level + 1, tree->leftNode);
    }
}

int main()
{
    char expression[BUFFER_SIZE];
    char revPolExpr[BUFFER_SIZE]; revPolExpr[0] = '\0';
    printf("Input expression: ");
    gets_s(expression);

    Stack stack;
    initStack(&stack);

    revPolandExpression(expression, revPolExpr);

    Tree tree;
    tree = buildTree(revPolExpr);

    printf("Reverse poland expression by stack: %s\n\n", revPolExpr);

    printf("All expressions by tree:\n");
    printf("Prefix: ");
    pref(tree);
    printf("\n");
    printf("Infix: ");
    inf(tree);
    printf("\n");
    printf("Postfix: ");
    post(tree);
    printf("\n\n");

    printf("Tree:\n");
    print_Tree(0, tree);

    return 0;
}
