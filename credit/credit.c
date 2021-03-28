#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number;

    number = get_long("Number: ");

    int a, b, c, d;

    int sum_1 = 0;
    int sum_2 = 0;
    int digits = 0;

    long n = number;
    long x = number;

    do
    {
        digits++;
        x /= 10;
    }
    while (x != 0);

    for (int i = 0; i < digits; i++)
    {
        a = n % 10;
        sum_2 = sum_2 + a;
        n /= 10;
        b = n % 10;
        n /= 10;
        c = b * 2;

        if (c < 10)
        {
            sum_1 = sum_1 + c;
        }
        else
        {
            d = c % 10;
            c /= 10;
            sum_1 = sum_1 + c + d;
        }
    }

    if (((sum_1 + sum_2)) % 10 == 0)
    {
        if ((digits == 15) && ((number / 10000000000000 == 34) || (number / 10000000000000 == 37)))
        {
            printf("AMEX\n");
        }

        else if ((digits == 16) && ((number / 100000000000000 >= 51) && (number / 100000000000000 <= 55)))
        {
            printf("MASTERCARD\n");
        }

        else if (((digits == 13) || (digits == 16)) && ((number / 1000000000000 == 4) || (number / 1000000000000000 == 4)))
        {
            printf("VISA\n");
        }

        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}