#include <stdio.h>

unsigned long long findOrder(int row, int column)
{
   unsigned long long n = row + column + 1;
   unsigned long long n2 = (n * (n + 1)) / 2;
   return n2 - row;
}

int main()
{
    unsigned long long multiply = 252533, remainder = 33554393;
    unsigned long long repeats = findOrder(2946, 3028) % remainder;
    unsigned long long code = 20151125;
    for (unsigned long long i = 0; i < repeats - 1; i++)
        code = (code * multiply) % remainder;

    printf("%llu\n", code);
}