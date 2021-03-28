#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;

    do
    {
        height = get_int("Height: ");
    }
    while ((height < 1) || (height > 8));

    int a = height;
    int b = 1;

// main loop 

    for (int i = 0; i < height; i++)
    {

        // first spaces
        for (int j = 1; j < a; j++)
        {
            printf(" ");

        }

        // first hashes
        for (int k = 0; k < b; k++)
        {
            printf("#");
        }

        // 2 spaces
        for (int l = 0; l < 2; l++)
        {
            printf(" ");
        }

        // last hashes
        for (int m = 0; m < b; m++)
        {
            printf("#");
        }

        printf("\n");
        b++;
        a--;
    }

}