#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);
    float L = (float)letters / (float)words * 100;
    float S = (float)sentences / (float)words * 100;
    float index1 = 0.0588 * L - 0.296 * S - 15.8; //The Coleman-Liau index
    int index2 = round(index1);

    if (index2 < 1) //Grading
    {
        printf("Before Grade 1\n");
    }
    else if (index2 >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", index2);
    }
}

int count_letters(string text)
{
    int lettercount = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        char c = text[i]; //seperate characters
        if (isalpha(c))
        {
            lettercount++;
        }
    }
    return lettercount;
}

int count_words(string text)
{
    int wordcount = 1;
    for (int i = 0; i < strlen(text); i++)
    {
        char c = text[i]; //seperate characters
        if (c == ' ') //counting words with spaces
        {
            wordcount++;
        }
    }
    return wordcount;
}

int count_sentences(string text)
{
    int sentencecount = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        char c = text[i]; //seperate characters
        if ((c == '!') || (c == '.') || (c == '?')) //counting sentences with !,. and ?
        {
            sentencecount++;
        }
    }
    return sentencecount;
}