#include <iostream>

static const int RAWS = 5;
static const int COLUMNS = 5;

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

void swapColumns(int (*arr)[COLUMNS], const int column1, const int column2)
{
    for (int i = 0; i < RAWS; ++i)
    {
        int temp = arr[i][column1];
        arr[i][column1] = arr[i][column2];
        arr[i][column2] = temp;
    }
}

int findSum(int(*arr)[COLUMNS], const int COLUMN, const int size)
{
    int sum = 0;
    for (int i = 0; i < size; ++i)
        sum += arr[i][COLUMN];
    return sum;
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

void task19(int (*arr)[COLUMNS])
{
    int colArr[COLUMNS];
    for (int i = 0; i < RAWS; ++i)
    {
        colArr[i] = findSum(arr, i, RAWS);
        printf("%d column:%d\n", i, colArr[i]);
    }
    for (int i = 1; i < COLUMNS; ++i)
        for (int j = 0; j < COLUMNS - i; ++j)
            if (colArr[j] < colArr[j + 1])
            {
                int temp = colArr[j];
                colArr[j] = colArr[j + 1];
                colArr[j + 1] = temp;
                swapColumns(arr, j, j+1);
            }
    printf("\n");
    for (int i = 0; i < RAWS; ++i)
        printf("%d column:%d\n", i, colArr[i]);
}

int main()
{
    srand(time(0));
    rand();
    int arr[RAWS][COLUMNS];
    fillArr(arr, 0, 9);
    printArr(arr);
    printf("\n");
    task19(arr);
    printf("\n");
    printArr(arr);
}

