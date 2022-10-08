#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int maxSize = 51;

struct Employe
{
    char lastName[maxSize];
    char department[maxSize];
    int salary;
};

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

void add(FILE *file, Employe *employe)
{
    printf("Input last name: ");
    gets_s(employe->lastName);
    printf("Input department: ");
    gets_s(employe->department);
    printf("Input salary: ");
    scanf("%d", &(employe->salary));
    fprintf(file, "%s %s %d\n", employe->lastName, employe->department, employe->salary);
}

int del(FILE *file, const char* lastName, const char* department)
{
        const int size = 1024;
        char pattern[size];

        fseek(file, 0, SEEK_END);
        char* storyData = new char[ftell(file) + 1];
        char* ptr = storyData;
        *ptr = 0;
        fseek(file, 0, SEEK_SET);

        int isPresent = 0;

        char lastNameBuf[51];
        char departmentBuf[51];

        while (fgets(pattern, size, file)) {
            extractName(lastNameBuf, pattern);
            extractDepartment(departmentBuf, pattern);
            if (strcmp(lastNameBuf, lastName) != 0 || strcmp(departmentBuf, department) != 0) {
                strcat(ptr, pattern);
                ptr += strlen(pattern);
            }
            else
                isPresent = 1;
        }

        fclose(file);
        file = fopen("database.txt", "w");
        fputs(storyData, file);

        free(storyData);
        return isPresent;
}

int edit(FILE *file, char* lastName, char* department, char* newName, char* newDepartment, int newSalary)
{
    const int size = 1024;
    char pattern[size];
    char newPattern[size];
    newPattern[0] = '\0';
    strcat(newPattern, newName);
    strcat(newPattern, " ");
    strcat(newPattern, newDepartment);
    strcat(newPattern, " ");
    char salaryStr[51];
    _itoa(newSalary, salaryStr, 10);
    strcat(newPattern, salaryStr);
    strcat(newPattern, "\n");

    int isPresent = 0;

    fseek(file, 0, SEEK_END);
    char* storyData = new char[ftell(file) + 1];
    char* ptr = storyData;
    *ptr = 0;
    fseek(file, 0, SEEK_SET);

    char lastNameBuf[51];
    char departmentBuf[51];
    int salaryBuf;

    while (fgets(pattern, size, file)) {
        extractName(lastNameBuf, pattern);
        extractDepartment(departmentBuf, pattern);
        salaryBuf = extractSalary(pattern);
        if (strcmp(lastNameBuf, lastName) != 0 || strcmp(departmentBuf, department) != 0) {
            strcat(ptr, pattern);
            ptr += strlen(pattern);
        }
        else
        {
            strcat(ptr, newPattern);
            ptr += strlen(newPattern);
            isPresent = 1;
        }
    }

    fclose(file);
    file = fopen("database.txt", "w");
    fputs(storyData, file);

    //delete[] storyData;
    free(storyData);
    return isPresent;
}

void calculateSalaries(FILE* file, char* department, int* totalSum, double* averageSalary)
{
    const int size = 1024;
    char pattern[size];
    int employesNum = 0;

    char departmentBuf[51];

    *totalSum = 0;
    *averageSalary = 0;

    while (fgets(pattern, size, file))
    {
        extractDepartment(departmentBuf, pattern);
        if (strcmp(departmentBuf, department) == 0)
        {
            *totalSum += extractSalary(pattern);
            employesNum++;
        }
    }
    *averageSalary = *totalSum / employesNum;
}

int main()
{
    int isStay = 1, option;
    FILE* file;
    Employe employe{};
    const char* path = "database.txt";
    char lastName[51];
    char department[51];
    int totalSum = 0;
    double averageSalary = 0;
    while (isStay)
    {
        printf("Input option: ");
        scanf("%d", &option);
        getchar();
        switch (option)
        {
        case 1:
            file = fopen(path, "a");
            add(file, &employe);
            fclose(file);
            break;
        case 2:
            file = fopen(path, "r"); 
            printf("Input last name: ");
            gets_s(lastName);
            printf("Input department: ");
            gets_s(department);

            if (!del(file, lastName, department))
                printf("There's no such employe!\n");
            fclose(file);
            break;
        case 3:
            printf("Input last name: ");
            gets_s(lastName);
            printf("Input department: ");
            gets_s(department);
            char newName[51];
            char newDepartment[51];
            int newSalary;
            printf("Input new last name: ");
            gets_s(newName);
            printf("Input new department: ");
            gets_s(newDepartment);
            printf("Input new salary: ");
            scanf("%d", &newSalary);
            file = fopen(path, "r");
            if (!edit(file, lastName, department, newName, newDepartment, newSalary))
                printf("There's no such employe!\n");
            fclose(file);
            break;
        case 4:
            printf("Input department: ");
            gets_s(department);
            file = fopen(path, "r");
            calculateSalaries(file, department, &totalSum, &averageSalary);
            fclose(file);
            printf("Total sum of salaries in department: %d\n", totalSum);
            printf("Average salary of employe in department: %lf\n", averageSalary);
            break;
        default:
            isStay = 0;
        }
    }
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
