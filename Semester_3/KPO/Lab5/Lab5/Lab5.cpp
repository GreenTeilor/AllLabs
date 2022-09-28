#include <stdio.h>
#include <string.h>
#include <iostream>
#include <ctime>

static const int databaseSize = 10;
static const int maxWordSize = 10;

int genRandInt(const int min, const int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void swap(char word1[maxWordSize + 1], char word2[maxWordSize + 1])
{
    char temp[maxWordSize + 1];
    strcpy_s(temp, word1);
    strcpy_s(word1, maxWordSize + 1, word2);
    strcpy_s(word2, maxWordSize + 1, temp);
}

void getNextWord(char* word, char* str, int* pos)
{
    int wordPos = 0;
    for (; *pos < strlen(str) && str[*pos] != ' ' && str[*pos] != '_'; ++(*pos))
    {
        word[wordPos] = str[*pos];
        ++wordPos;
    }
    word[wordPos] = '\0';
    ++(*pos);
}

void task28(char* encryptedStr, char* str, char(*database)[maxWordSize + 1])
{
    //Randomize database words
    for (int i = 0; i < databaseSize - 1; ++i)
        swap(database[i], database[genRandInt(0, databaseSize - 2)]);
    
    //If count == 0 then output word from str, otherwise output word from database
    int que = 1;
    int i = 0, count = 0;
    char word[maxWordSize + 1];

    while (i < strlen(str))
    {
        if (que == 0)
        {
            getNextWord(word, str, &i);
            strcat_s(encryptedStr, 200 , word);
            strcat_s(encryptedStr, 200, "_");
        }
        else
        {
            strcat_s(encryptedStr, 200, database[count]);
            strcat_s(encryptedStr, 200, "_");
            ++count;
        }

        ++que;
        que %= 3;
    }
    encryptedStr[strlen(encryptedStr) - 1] = '\0';

}



int main()
{
    srand(time(0));
    rand();
    //setlocale(LC_ALL, "Russian");
    char database[databaseSize][maxWordSize + 1];
    char str[100];
    char encryptedStr[200] = {};
    int chosenWords[databaseSize];
    for (int i = 0; i < databaseSize; ++i)
    {
        printf("Input %d database word: ", i + 1);
        gets_s(database[i]);
    }
    printf("Input string: ");
    gets_s(str);
    task28(encryptedStr, str, database);
    puts(encryptedStr);
}
