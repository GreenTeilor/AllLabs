#include <stdio.h>
#include <string.h>

void task1(char* str)
{ 
    int i = 0, minLength = 80, minIndex, maxLength = 0, maxIndex, currentLength;
    char maxWord[20];
    char minWord[20];
    char newStr[80] = "";
    while (str[i] != '\0')
    {
        if (str[i] != ' ')
        {
            currentLength = 0;
            while (str[i] != ' ' && str[i] != '\0')
            {
                ++currentLength;
                ++i;
            }
            if (currentLength > maxLength)
            {
                maxLength = currentLength;
                maxIndex = i - maxLength;
            }
            if (currentLength < minLength)
            {
                minLength = currentLength;
                minIndex = i - minLength;
            }
        }
        if (str[i] != '\0')
            ++i;
    }
    for (int j = maxIndex; j < maxIndex + maxLength; ++j)
        maxWord[j - maxIndex] = str[j];
    maxWord[maxLength] = '\0';
    for (int j = minIndex; j < minIndex + minLength; ++j)
        minWord[j - minIndex] = str[j];
    minWord[minLength] = '\0';
    

    //Copy string until meet longest or shortest word
    int indexOriginal = 0;
    int indexNew = 0;
    while (indexOriginal != ((minIndex < maxIndex) ? minIndex : maxIndex))
    {
        newStr[indexNew] = str[indexOriginal];
        ++indexOriginal;
        ++indexNew;
    }

    newStr[indexNew] = '\0';

    //Concat 1-st string
    if (minIndex < maxIndex)
    {
        strcat_s(newStr, maxWord);
        indexNew += maxLength;
        indexOriginal += minLength;
    }
    else
    {
        strcat_s(newStr, minWord);
        indexNew += minLength;
        indexOriginal += maxLength;
    }

    //Copy string until meet longest or shortest word
    while (indexOriginal != ((minIndex > maxIndex) ? minIndex : maxIndex))
    {
        newStr[indexNew] = str[indexOriginal];
        ++indexOriginal;
        ++indexNew;
    }

    newStr[indexNew] = '\0';

    //Concat 2-st string
    if (minIndex > maxIndex)
    {
        strcat_s(newStr, maxWord);
        indexNew += maxLength;
        indexOriginal += minLength;
    }
    else
    {
        strcat_s(newStr, minWord);
        indexNew += minLength;
        indexOriginal += maxLength;
    }

    //Copy to the end of the string
    while (str[indexOriginal] != '\0')
    {
        newStr[indexNew] = str[indexOriginal];
        ++indexOriginal;
        ++indexNew;
    }

    newStr[indexNew] = '\0';

    int j = -1;
    while (newStr[j++] != '\0')
        str[j] = newStr[j];


}

void task2(char* str)
{
    int i = 0;
    if (str[i] >= 'a' && str[i] <= 'z')
        str[i] += 'A' - 'a';
    ++i;
    while (str[i] != '\0')
    {
        if (str[i] >= 'a' && str[i] <= 'z' && str[i - 1] == ' ')
            str[i] += 'A' - 'a';
        ++i;
    }
}

void task3(char* str)
{
    int i = 0;
    int strSize = 0;
    while (str[i] != '\0')
    {
        ++strSize;
        ++i;
    }
    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] >= '0' && str[i] <= '9' && (i & 1) != 0)
        {
            int temp = (i + 1) % strSize;
            char tempSwap;
            while (!(str[temp] >= 'a' && str[temp] <= 'z'))
                temp = (temp + 2) % strSize;
            tempSwap = str[i];
            str[i] = str[temp];
            str[temp] = tempSwap;
        }
        ++i;
    }
}

int main()
{
    //Task 1
    char str[80];
    printf("Input string: ");
    gets_s(str);
    task1(str);
    printf("Result: ");
    puts(str);

    printf("\n============================\n\n");

    //Task 2
    printf("Input string: ");
    gets_s(str);
    task2(str);
    printf("Result: ");
    puts(str);

    printf("\n============================\n\n");

    //Task 3
    printf("Input string: ");
    gets_s(str);
    task3(str);
    printf("Result: ");
    puts(str);

}
