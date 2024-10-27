#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK_SIZE 512

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //usage check
    if (argc != 2)
    {
        printf("Usage: ./recover <file.raw>\n");
        return 1;
    }
    //open file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open %s\n", argv[1]);
        return 1;
    }


    BYTE buffer[512];

    //for first header
    int headerDetected = 0;

    //jpeg number tracker
    int track = 0;

    char filename[8];
    FILE *img = NULL;

    //reading memory card until the end
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        //checking header
        if ((buffer[3] & 0xF0) == 0xE0 && buffer[2] == 0xFF && buffer[1] == 0xD8 && buffer[0] == 0xFF)
        {
            headerDetected = 1;
            //first header
            if (track == 0)
            {
                sprintf(filename, "%03i.jpg", track++);
                img = fopen(filename, "w");
                fwrite(&buffer, sizeof(BYTE), BLOCK_SIZE, img);
            }
            //other headers
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", track++);
                img = fopen(filename, "w");
                fwrite(&buffer, sizeof(BYTE), BLOCK_SIZE, img);
            }
        }
        else
        {
            if (headerDetected == 1)
            {
                fwrite(&buffer, sizeof(BYTE), BLOCK_SIZE, img);
            }
        }
    }

    //closing files
    fclose(img);
    fclose(file);

}