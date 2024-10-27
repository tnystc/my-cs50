// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 17576;

unsigned long wordCounter = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    unsigned int hashIndex = hash(word);
    node *trav = table[hashIndex];
    while (trav != NULL)
    {
        if (strcasecmp(word, trav->word) == 0)
        {
            return true;
        }
        trav = trav->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned int firstLetter = toupper(word[0]) - 'A';
    if (strlen(word) == 2)
    {
        unsigned int secondLetter = toupper(word[1]) - 'A';
        return firstLetter * 26 + secondLetter;
    }
    else if (strlen(word) == 1)
    {
        return firstLetter;
    }
    else
    {
        unsigned int secondLetter = toupper(word[1]) - 'A';
        unsigned int thirdLetter = toupper(word[2]) - 'A';
        return firstLetter * 26 * 26 + secondLetter * 26 + thirdLetter;
    }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        unsigned int hashIndex = hash(word);
        strcpy(n->word, word);
        n->next = table[hashIndex];
        table[hashIndex] = n;
        wordCounter++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return wordCounter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *trav = table[i];
        while (trav != NULL)
        {
            node *tmp = trav;
            trav = trav->next;
            free(tmp);
        }
        if (trav == NULL && i == N - 1)
        {
            return true;
        }
    }
    return false;
}
