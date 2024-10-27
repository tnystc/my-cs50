#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            //calculate average rgb amount
            int avg = round((image[row][col].rgbtGreen + image[row][col].rgbtRed + image[row][col].rgbtBlue) / 3.0);
            image[row][col].rgbtBlue = image[row][col].rgbtGreen = image[row][col].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            //sepia algorithm
            int sepiaBlue = round(.272 * image[row][col].rgbtRed + .534 * image[row][col].rgbtGreen + .131 * image[row][col].rgbtBlue);
            int sepiaGreen = round(.349 * image[row][col].rgbtRed + .686 * image[row][col].rgbtGreen + .168 * image[row][col].rgbtBlue);
            int sepiaRed = round(.393 * image[row][col].rgbtRed + .769 * image[row][col].rgbtGreen + .189 * image[row][col].rgbtBlue);
            //check for values
            image[row][col].rgbtBlue = (sepiaBlue > 255) ? 255 : sepiaBlue;
            image[row][col].rgbtGreen = (sepiaGreen > 255) ? 255 : sepiaGreen;
            image[row][col].rgbtRed = (sepiaRed > 255) ? 255 : sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width / 2; col++)
        {
            RGBTRIPLE tmp = image[row][col];
            image[row][col] = image [row][width - (col + 1)];
            image[row][width - (col + 1)] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];

    //create a temporary copy to save blur data
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            tmp[row][col] = image[row][col];
        }
    }

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int totalRed, totalGreen, totalBlue;
            totalRed = totalGreen = totalBlue = 0;
            float pixelNumber = 0;

            //coordinates for validation
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    int currentX = row + x;
                    int currentY = col + y;

                    if (currentX < 0 || currentX > (height - 1))
                    {
                        continue;
                    }

                    if (currentY < 0 || currentY > (width - 1))
                    {
                        continue;
                    }

                    totalRed += image[currentX][currentY].rgbtRed;
                    totalGreen += image[currentX][currentY].rgbtGreen;
                    totalBlue += image[currentX][currentY].rgbtBlue;
                    pixelNumber++;
                }
                //calculate average and save to temporary image
                tmp[row][col].rgbtRed = round(totalRed / pixelNumber);
                tmp[row][col].rgbtGreen = round(totalGreen / pixelNumber);
                tmp[row][col].rgbtBlue = round(totalBlue / pixelNumber);
            }

        }
    }
    //copy to original
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            image[row][col].rgbtRed = tmp[row][col].rgbtRed;
            image[row][col].rgbtGreen = tmp[row][col].rgbtGreen;
            image[row][col].rgbtBlue = tmp[row][col].rgbtBlue;
        }
    }
    return;
}
