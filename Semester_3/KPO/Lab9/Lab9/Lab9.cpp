#include <iostream>
#include <stdio.h>

struct List
{
    double value;
    List* next;
};

void alcMem(List** head, const int elemCount)
{
    *head = (List*)malloc(sizeof(List));
    List* temp = *head;
    double value;
    for (int i = 0; i < elemCount; ++i)
    {
        (*head)->next = (List*)malloc(sizeof(List));
        *head = (*head)->next;
        printf("Input value of %d element: ", i + 1);
        scanf_s("%lf", &value);
        (*head)->value = value;
        (*head)->next = NULL;
    }
    *head = temp;

}

int cmp(const double val1, const double val2, const double eps)
{
    if ((val1 - val2) < eps)
        return 1;
    return 0;
}

void task(List** head)
{
    List* temp = *head;
    while ( *head != NULL)
    {
        if (*head != NULL &&  (*head)->next != NULL && (*head)->next->next != NULL)
        if (cmp((*head)->next->next->value, 1, 0.1))
        {
            List* mem = (*head)->next;
            (*head)->next = (*head)->next->next;
            free(mem);
        }
        if (*head != NULL)
            *head = (*head)->next;
    }
    *head = temp;
}

void printList(List const* head)
{
    head = head->next;
    while (head != NULL)
    {
        printf("%lf ", head->value);
        head = head->next;
    }
}

int main()
{
    List* head;
    alcMem(&head, 10);
    printList(head);
    task(&head);
    printf("\n");
    printList(head);
}

