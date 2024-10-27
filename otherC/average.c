#include <stdio.h>
#include <cs50.h>

float average(int array[]);

const int n = 3;

int main(void)
{
    int scores[n];
    for (int i = 0; i < n; i++)
    {
        scores[i] = get_int("Enter your score: ");
    }
    printf("%f\n", average(scores));
}

float average(int array[])
{
    int sum = 0;
    for (int x = 0; x < n; x++)
    {
        sum += array[x];
    }
    return sum / (float) n;
}