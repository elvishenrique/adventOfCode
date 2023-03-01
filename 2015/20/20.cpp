#include <stdio.h>

int divisor_sum(int n)
{
    int sum = 0;
    for (int i = 1; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            if (i * i != n)
                sum += i + (n / i);
            else
                sum += i;
        }
    }

    return sum;
}

int divisor_bounded(int n)
{
    int sum = 0;
    for (int i = n; i >= n / i && 50 * i >= n; i--)
    {
        if (n % i == 0)
        {
            if (i * i != n)
            {
                if (i > 50)
                    sum += i;
                else
                    sum += i + (n / i);
            }
            else if (i <= 50)
            {
                sum += i;
            }
        }
    }

    return sum;
}

int main()
{
    int i = 1, s = 10 * divisor_sum(i);
    while (s < 36000000)
    {
        i++;
        s = 10 * divisor_sum(i);
    }

    printf("%d\n", i);
    printf("%d\n", 10 * divisor_sum(i));

    s = 11 * divisor_bounded(i);
    while (s < 36000000)
    {
        i++;
        s = 11 * divisor_bounded(i);
    }

    printf("%d\n", i);
    printf("%d\n", 11 * divisor_bounded(i));
}
