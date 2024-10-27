#include <cs50.h>
#include <stdio.h>

int main(void)
{

    int height;

    do
    {
        height = get_int("Enter a height value: ");     //getting height from user
    }
    while (height < 1 || height > 8);


    for (int n = 1; n <= height; n++)  //n is the number of # in each side
    {
        for (int j = 0; j < height - n; j++)     //space counter for rows
        {
            printf(" ");
        }

        int firsthash = 0;

        while (firsthash < n)     //first hash counter
        {
            printf("#");
            firsthash++;
        }

        if (n == firsthash)    //space between hash series
        {
            printf("  ");
        }

        for (int secondhash = 0; secondhash < n; secondhash++)     //second hash counter
        {
            printf("#");
        }

        printf("\n");

    }

}