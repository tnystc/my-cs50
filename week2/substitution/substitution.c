#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void enciphering(string key, string plaintext);

int main(int argc, string argv[])
{
    if (argc != 2) //checking proper usage
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];

    if (strlen(key) != 26) //checking character count
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    int duplicationcheck = 0;
    int alphabetcheck = 0;

    for (int i = 0; i < 26; i++) //scan for non-alphabetic and repeatedn characters
    {
        if (!isalpha(key[i]))
        {
            alphabetcheck++;
        }

        for (int j = 0; j < 26; j++)
        {
            if (key[i] == key[j])
            {
                duplicationcheck++;
            }
        }
    }

    if (alphabetcheck != 0)
    {
        printf("Key must only contain alphabetic characters.\n");
        return 1;
    }

    if (duplicationcheck != 26)
    {
        printf("Key must not contain repeated characters.\n");
        return 1;
    }


    string plaintext = get_string("Plaintext: "); //Getting plaintext
    printf("ciphertext: ");
    enciphering(key, plaintext);

    printf("\n");

}

void enciphering(string key, string plaintext)
{
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (isalpha(plaintext[i]))
        {
            int j = 0; // j is index
            while (toupper(plaintext[i]) != alphabet[j]) //matching index
            {
                j++;
            }
            if (isupper(plaintext[i])) //checking upper or lower
            {
                printf("%c", toupper(key[j]));
            }
            else if (islower(plaintext[i]))
            {
                printf("%c", tolower(key[j]));
            }
        }
        else
        {
            printf("%c", plaintext[i]); //printing non-alphabetic characters
        }
    }
}