#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2) //checking key
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isdigit(argv[1][i])) //checking key
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }

    }

    int key = atoi(argv[1]); //converting key to integer
    string plaintext = get_string("Plaintext: "); //getting text
    printf("Ciphertext: ");

    for (int j = 0; j < strlen(plaintext); j++) //enciphering process
    {
        if (isupper(plaintext[j]))
        {
            printf("%c", (plaintext[j] - 'A' + key) % 26 + 'A');
        }
        else if (islower(plaintext[j]))
        {
            printf("%c", (plaintext[j] - 'a' + key) % 26 + 'a');
        }
        else
        {
            printf("%c", plaintext[j]);
        }
    }

    printf("\n");
}