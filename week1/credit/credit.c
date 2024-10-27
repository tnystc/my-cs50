#include <stdio.h>
#include <cs50.h>

int length_counter(long cardnumber);
int luhn_algorithm(long cardnumber);
int starting_digits(long cardnumber);

int main(void)
{
    //getting card number
    long cardnumber = get_long("Number: ");

    int cardlenght = length_counter(cardnumber);

    if (cardlenght != 16 && cardlenght != 15 && cardlenght != 13)
    {
        printf("INVALID\n");
        return 0;
    }

    int check1 = luhn_algorithm(cardnumber);

    //Luhn validation
    if (check1 % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }

    int check2 = starting_digits(cardnumber);

    //Matching card numbers
    if ((check2 / 10 == 3) && (check2 % 10 == 4 || check2 % 10 == 7))
    {
        printf("AMEX\n");
    }
    else if (check2 / 10 == 4)
    {
        printf("VISA\n");
    }
    else if ((check2 / 10 == 5) && (check2 % 10 <= 5 && check2 % 10 >= 1))
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

// Counting lenght
int length_counter(long cardnumber)
{
    int counter = 0;
    long i = cardnumber;
    while (i > 0)
    {
        i /= 10;
        counter++;
    }
    return counter;
}

//Validation algorithm
int luhn_algorithm(long cardnumber)
{
    int firstsum = 0; 
    int secondsum = 0;
    int finalsum = 0;
    int mod1;
    int mod2;
    int x2_1; //x2 represents doubled digits
    int x2_2;

    do
    {
        //Last digit
        mod1 = cardnumber % 10;
        cardnumber /= 10;
        firstsum += mod1;

        //Second to last digit
        mod2 = cardnumber % 10;
        cardnumber /= 10;

        //Multiply by 2 and seperate digit
        mod2 *= 2;
        x2_1 = mod2 % 10;
        x2_2 = mod2 / 10;
        secondsum = secondsum + x2_1 + x2_2;

    }
    while (cardnumber > 0);
    finalsum = firstsum + secondsum;
    return finalsum;
}

//First two digits
int starting_digits(long cardnumber)
{
    long j = cardnumber;
    do
    {
        j /= 10;
    }
    while (j > 100);
    return j;
}