#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student
{
    unsigned int groupNum;
    char lastName[256];
    double averageGrade;
};

void task12(Student* groups, unsigned int size)
{
    for (int i = 0; i < size - 1; ++i)
        for (int j = 0; j < size - i - 1; ++j)
            if (groups[j].groupNum > groups[j + 1].groupNum)
            {
                Student temp;
                temp = groups[j];
                groups[j] = groups[j + 1];
                groups[j + 1] = temp;
            }

    int i = 0;
    while (i < size)
    {
        unsigned int groupNum = groups[i].groupNum;
        int currentSize = 0;
        while (groupNum == groups[i + currentSize].groupNum && i < size)
            ++currentSize;
        int firstIndex = i;
        for (int count = 1; count < size; ++count)
            for (int j = firstIndex; j < firstIndex + currentSize - count; ++j)
                if (groups[j].averageGrade < groups[j + 1].averageGrade)
                {
                    Student temp;
                    temp = groups[j];
                    groups[j] = groups[j + 1];
                    groups[j + 1] = temp;
                }
       for (int count = firstIndex; count < firstIndex + currentSize; ++count)
        {
            printf("Group: %d\n", groups[count].groupNum);
            printf("Last name: ");
            puts(groups[count].lastName);
            printf("Average grade: %lf\n", groups[count].averageGrade);
            printf("\n");
        }
        printf("\n\n\n");
        i += currentSize;
    }
}

int main()
{
    unsigned int studentNum;
    printf("Input number of students: ");
    scanf_s("%d",& studentNum);
    getchar();
    Student* students = (Student*)calloc(studentNum, sizeof(Student));

    for (int i = 0; i < studentNum; ++i)
    {
        printf("Input student %d group: ", i + 1);
        scanf_s("%d", &students[i].groupNum);
        getchar();
        printf("Input student %d last name: ", i + 1);
        gets_s(students[i].lastName, 256);
        printf("Input student %d average grade: ", i + 1);
        scanf_s("%lf", &students[i].averageGrade);
        getchar();
    }
    printf("\n");

    task12(students, studentNum);

}