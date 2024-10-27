#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

#define HEADER_SIZE 44

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav/n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        printf("Could not open %s/n", argv[1]);
    }

    // Read header into an array
    // TODO #3
    WAVHEADER buffHeader;
    fread(&buffHeader, sizeof(BYTE), HEADER_SIZE, inptr);

    // Use check_format to ensure WAV format
    // TODO #4
    if (check_format(buffHeader) == 1)
    {
        printf("Input is not a WAV file./n");
        return 1;
    }

    // Open output file for writing
    // TODO #5
    FILE *outptr = fopen(argv[2], "w");
    if (outptr == NULL)
    {
        printf("Could not create %s/n", argv[2]);
    }


    // Write header to file
    // TODO #6
    fwrite(&buffHeader, sizeof(BYTE), HEADER_SIZE, outptr);

    // Use get_block_size to calculate size of block
    // TODO #7
    int block_size = get_block_size(buffHeader);

    // Write reversed audio to file
    // TODO #8
    BYTE buffer[block_size];
    fseek(inptr, 0, SEEK_END);
    int numSample = buffHeader.subchunk2Size / block_size;
    for (int i = 1; i <= numSample; i++)
    {
        fseek(inptr, -i * block_size, SEEK_END);
        fread(&buffer, block_size, 1, inptr);
        fwrite(&buffer, block_size, 1, outptr);
    }



    fclose(inptr);
    fclose(outptr);

}

int check_format(WAVHEADER header)
{
    // TODO #4
    if (header.format[0] == 'W' && header.format[1] == 'A' && header.format[2] == 'V' && header.format[3] == 'E')
    {
        return 0;
    }
    else
    {
        return 1;
    }

}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    return header.numChannels * header.bitsPerSample / 8;
}
