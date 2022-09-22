#include <stdio.h>
#include <cmath>
#include <iostream>

using namespace std;

int task10(const unsigned int n)
{
    return (int)pow(2, n);
}

double task11(const double a, const unsigned int n, const bool var)
{
    double res{ a };
    for (unsigned int i = 0; i < n - 1; ++i)
        res *= a + i + 1;
    return (var) ? pow(a, n) : res;
}

double task13()
{
    double res{ 1 + sin(0.1) };
    for (int i = 0; i < 10; ++i)
        res *= 1 + sin((i + 1) / 10);
    return res;
}

double task16()
{
    double res{ 1 };
    for (int i = 0; i < 99; ++i)
        res += 1 / pow((i + 2), 2);
    return res;
}

double task17()
{
    double res{ 1 };
    for (int i = 0; i < 49; ++i)
        res += 1 / pow((i + 2), 3);
    return res;
}

int main()
{
    //Task 10 
    unsigned int n;
    printf("Input n: ");
    scanf_s("%d", &n);
    printf("%d",task10(n));

    printf("%c", '\n');

    //Task 11
    double a;
    printf("Input n: ");
    scanf_s("%d", &n);
    printf("Input a: ");
    scanf_s("%lf", &a);
    printf("%lf", task11(a, n, true));

    printf("%c", '\n');

    //Task 13
    printf("%lf", task13());

    printf("%c", '\n');

    //Task 16
    printf("%lf", task16());

    printf("%c", '\n');

    //Task 17
    printf("%lf", task17());
    

    return 0;
}

