#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Check for command line args
    if (argc != 2)
    {
        printf("Usage: ./read infile\n");
        return 1;
    }

    // Create buffer to read into
    char *buffer;
    buffer = malloc(7 * sizeof(char));

    // Create array to store plate numbers
    char **plates;
    plates = malloc(8 * sizeof(char*));
    for (int i = 0; i < 8; i++)
    {
        plates[i] = malloc(7 * sizeof(char));
    }

    FILE *infile = fopen(argv[1], "r");

    int idx = 0;

    while (fread(buffer, 1, 7, infile) == 7)
    {
        // Replace '\n' with '\0'
        buffer[6] = '\0';

        // Save plate number in array
        strcpy(plates[idx], buffer);
        idx++;
    }

    for (int i = 0; i < 8; i++)
    {
        printf("%s\n", plates[i]);
    }

    free(buffer);
    for (int i = 0; i < 8; i++)
    {
        free(plates[i]);
    }
    free(plates);
    fclose(infile);
}
