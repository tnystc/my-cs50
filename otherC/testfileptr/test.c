#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *inptr = fopen("input.txt", "r");
    int headBuffer[2];
    fread(&headBuffer, 1, 2, inptr);

    FILE *outptr = fopen("output.txt", "w");
    fwrite(&headBuffer, 1, 2, outptr);

    int buffer[6];
    fseek(inptr, 0, SEEK_END);
    int ft = ftell(inptr);
    printf("%i\n", ft);
    int i = 0;
    while(i < ft - 2)
    {
        i++;
        fseek(inptr, -i, SEEK_END);
        fread(&buffer, 1, 1, inptr);
        fwrite(&buffer, 1, 1, outptr);

    }





    fclose(inptr);
    fclose(outptr);




}