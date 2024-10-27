#include <stdio.h>
#include <cs50.h>

int factorial(int n);

int main(void)
{
    int n = get_int("Enter number: ");
    printf("%i\n", factorial(n));
}

int factorial(int n)
{
    if (n > 0)
    {
        return n * factorial(n - 1);
    }
    else
    {
        return 1;
    }
}