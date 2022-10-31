#include <iostream>
#include <stdlib.h>
#include <stdio.h>

struct Stack
{
    int m_info;
    Stack* m_next;
};

typedef Stack* TStack;

void push(TStack* stack, const int info)
{
    TStack temp = *stack;
    *stack = (TStack)malloc(sizeof(stack));
    (*stack)->m_info = info;
    (*stack)->m_next = temp;
}

int pop(TStack* stack)
{
    TStack temp = *stack;
    int info = (*stack)->m_info;
    *stack = (*stack)->m_next;
    //free(temp);
    return info;
}

void task2(TStack* stack)
{
    while (*stack != NULL && !((*stack)->m_info & 1))
    {
        TStack temp = *stack;
        *stack = (*stack)->m_next;
        //free(temp);
    }

    TStack top = *stack;
    TStack prev = *stack;
    if (*stack != NULL)
        *stack = (*stack)->m_next;

    while (*stack != NULL)
    {

        if (!((*stack)->m_info & 1))
        {
            prev->m_next = (*stack)->m_next;
            //free(*stack);
            *stack = prev->m_next;
        }
        else
        {
            *stack = (*stack)->m_next;
            prev = prev->m_next;
        }


    }

    *stack = top;

    printf("All even numbers were succesfully deleted!\n\n");
}

void print(TStack stack)
{
    printf("Stack: ");
    while (stack != NULL)
    {
        printf("%d ", stack->m_info);
        stack = stack->m_next;
    }
    printf("\n\n");
}

int main()
{
    TStack stack = NULL;
    int option{ 0 };
    while (option != 5)
    {
        scanf_s("%d", &option);
        getchar();
        switch (option)
        {
        case 1:
        {
            int info;
            printf("Input value: ");
            scanf_s("%d", &info);
            getchar();
            push(&stack, info);
            printf("Element %d pushed succesfully!\n\n", info);
            break;
        }
        case 2:
        {
            printf("Element %d poped succesfully!\n\n", pop(&stack));
            break;
        }
        case 3:
        {
            print(stack);
            break;
        }
        case 4:
        {
            task2(&stack);
            break;
        }
        case 5:
            option = 5;
            break;
        }
    }
}
