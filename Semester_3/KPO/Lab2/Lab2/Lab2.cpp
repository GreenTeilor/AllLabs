#include <iostream>
#include <ctime>
#include <stdio.h>

static const int RAWS = 6;
static const int COLUMNS = 6;

int genRandInt(const int min, const int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void fillArr(int(*arr)[COLUMNS], const int min, const int max)
{
    for (int i = 0; i < RAWS; ++i)
        for (int j = 0; j < COLUMNS; ++j)
            arr[i][j] = genRandInt(min, max);
}

void printArr(int(*arr)[COLUMNS])
{
    for (int i = 0; i < RAWS; ++i)
    {
        for (int j = 0; j < COLUMNS; ++j)
            printf("%d\t", arr[i][j]);
        printf("\n");
    }           
}

void task24(int (*arr)[COLUMNS])
{
    int arrCopy[RAWS][COLUMNS];
    for (int i = 0; i < RAWS; ++i)
        for (int j = 0; j < COLUMNS; ++j)
            arrCopy[i][j] = arr[i][j];
    for (int i = 0; i < RAWS; ++i)
        for (int j = 0; j < COLUMNS; ++j)
            arr[i][j] = 0;
    for (int i = 0; i < RAWS; ++i)
        for (int j = 0; j < COLUMNS; ++j)
            for (int k = 0; k < RAWS; ++k)
                for (int t = j; t < COLUMNS; ++t)
                    if (k == i && t == j)
                        ;
                    else
                    {

                        if (arrCopy[i][j] == arrCopy[k][t])
                        {
                            arr[i][j] = 1;
                            arr[k][t] = 1;
                        }
                    }
}

int findMin(int* arr, const int size)
{
    int min = arr[0];
    for (int i = 1; i < size; ++i)
        if (arr[i] < min)
            min = arr[i];
    return min;
}

int findMax(int* arr, const int size)
{
    int max = arr[0];
    for (int i = 1; i < size; ++i)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

void task21(int(*arr)[COLUMNS], int& even, int& odd)
{
    even = 0;
    odd = 0;
    for (int i = 0; i < RAWS; ++i)
        if (i & 1)
            odd += findMin(arr[i], COLUMNS);
        else
            even += findMax(arr[i], COLUMNS); 
}

int main()
{
    srand(time(0));
    rand();
    int arr[6][6];
    fillArr(arr, 2, 15);
    arr[5][5] = 22;
    arr[0][2] = 21;
    printArr(arr);
    printf("\n");

    //Task 21
    int num1, num2;
    task21(arr, num1, num2);
    printf("%d  ", num1);
    printf("%d  ", num2);
    printf("\n");

    //Task 24
    task24(arr);
    printf("\n");
    printArr(arr);
}

