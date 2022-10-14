#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

const int maxSize = 51;
const char* path1 = "database.txt";
const char* path2 = "bad.txt";

struct Student
{
    char lastName[maxSize];
    char group[maxSize];
    int grade;
};

void add(FILE* file, Student* student)
{
    printf("Input last name: ");
    gets_s(student->lastName);
    printf("Input department: ");
    gets_s(student->group);
    printf("Input salary: ");
    scanf("%d", &(student->grade));
    fprintf(file, "%s %s %d\n", student->lastName, student->group, student->grade);
    fclose(file);
}

void extractName(char* buffer, char* source)
{
    buffer[0] = '\0';
    int i = 0;
    while (source[i] != ' ')
    {
        buffer[i] = source[i];
        i++;
    }
    buffer[i] = '\0';
}

void extractDepartment(char* buffer, char* source)
{
    int i = 0;
    while (source[i] != ' ')
    {
        i++;
    }
    i++;
    int count = 0;
    while (source[i] != ' ')
    {
        buffer[count] = source[i];
        i++;
        count++;
    }
    buffer[count] = '\0';
}

int extractSalary(char* source)
{
    int i = 0;
    char buffer[maxSize];
    while (source[i] != ' ')
    {
        i++;
    }
    i++;
    while (source[i] != ' ')
    {
        i++;
    }
    i++;
    int count = 0;
    while (source[i] != '\0')
    {
        buffer[count] = source[i];
        i++;
        count++;
    }
    buffer[count] = '\0';
    i = atoi(buffer);
    return i;
}

int del(FILE* file, FILE* fileBAD)
{
    const int size = 1024;
    char pattern[size];

    fseek(file, 0, SEEK_END);
    char* storyData = new char[ftell(file) + 1];
    char* ptr = storyData;
    *ptr = 0;
    fseek(file, 0, SEEK_SET);

    int isPresent = 0;
    int salaryBuf;

    char lastNameBuf[51];
    char departmentBuf[51];

    while (fgets(pattern, size, file)) {
        extractName(lastNameBuf, pattern);
        extractDepartment(departmentBuf, pattern);
        salaryBuf = extractSalary(pattern);
        if (salaryBuf >= 4) {
            strcat(ptr, pattern);
            ptr += strlen(pattern);
        }
        else
        {
            fprintf(fileBAD, "%s %s %d\n", lastNameBuf, departmentBuf, salaryBuf);
            isPresent = 1;
        }
    }

    fclose(file);
    fclose(fileBAD);
    file = fopen("database.txt", "w");
    fputs(storyData, file);

    delete[] storyData;
    fclose(file);
    return isPresent;
}

int genRandInt(const int min, const int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void task1(FILE* file, FILE* fileBAD)
{
    const int size = 1024;
    char pattern[size];
    int intPattern;

    //Fullfill original file
    for (int i = 0; i < 10; ++i)
       fprintf(file, "%d\n", genRandInt(-6, 5));

    //fprintf(file, "-4\n1\n0\n-1\n-5\n1\n3\n3\n0\n-2\n");

    fclose(file);

    file = fopen(path1, "r");

    while (fgets(pattern, size, file))
    {
        intPattern = atoi(pattern);
        if (intPattern >= 0)
            fprintf(fileBAD, "%d\n", intPattern);
            
    }

    fclose(file);
}

int main()
{
    srand(time(0));
    rand();
    FILE* file;
    FILE* fileBAD;
    Student* student = (Student*)malloc(sizeof(Student));
    int isMenu = 1;
    int option;

    while (isMenu)
    {
        printf("Input option: ");
        scanf("%d", &option);
        getchar();
        switch (option)
        {
        case 1:
            file = fopen(path1, "a");
            add(file, student);
            break;

        case 2:
            file = fopen(path1, "r");
            fileBAD = fopen(path2, "w");
            del(file, fileBAD);
            break;
        case 3:
            file = fopen(path1, "w");
            fileBAD = fopen(path2, "w");
            task1(file, fileBAD);
            break;
        default:
            isMenu = 0;
        }
    }

    free(student);
}

/* =====WORK WITH FILES======

*#include <stdio.h>

* ----TEXT FILES----

    //Create file
    FILE *file = fopen(const char *file_path, const char *type);
    types:
        w - write(open file, erasing all inside it, if file doesn't exist, create one)
        r - read(open file in read-only state, if file doesn't exist - ERROR)
        r+ - read and write operations allowed(open file without erasing information, if file doesn't exist - ERROR)
        a - append(open file, doesn't erase information inside file, allows to append information in file, if file doesn't exist, create one)

    //Close file
    fclose(FILE *file);

    //Write in file
    fprintf(FILE *file, const char *string);

    //Read from file
    fgets(char *buffer, int max_length, FILE *file);

    //End of the file
    feof(FILE *file);

* ----BINARY FILES----

    //Create file
    FILE *file = fopen(const char *file_path, const char *type);
        types:
        w - write(open file, erasing all inside it, if file doesn't exist, create one)
        r - read(open file in read-only state, if file doesn't exist - ERROR)
        r+ - read and write operations allowed(open file without erasing information, if file doesn't exist - ERROR)
        a - append(open file, doesn't erase information inside file, allows to append information in file, if file doesn't exist, create one)

    //Close file
    fclose(FILE *file);

    //Write in file
    fwrite(const void *pointer, int count, int size, FILE *file);

    //Read from file
    fread(const void *pointer, int count, int size, FILE *file);

    //End of the file
    feof(FILE *file);

    ---A LOT OF EXAMPLES IN NOTION---

*/

