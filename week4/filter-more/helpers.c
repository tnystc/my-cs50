#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    RGBTRIPLE tmp[height][width];

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int gxBlue = 0;
            int gyBlue = 0;
            int gxGreen = 0;
            int gyGreen = 0;
            int gxRed = 0;
            int gyRed = 0;

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

                    gxBlue += image[row + x][col + y].rgbtBlue * gx[x + 1][y + 1];
                    gyBlue += image[row + x][col + y].rgbtBlue * gy[x + 1][y + 1];
                    gxGreen += image[row + x][col + y].rgbtGreen * gx[x + 1][y + 1];
                    gyGreen += image[row + x][col + y].rgbtGreen * gy[x + 1][y + 1];
                    gxRed += image[row + x][col + y].rgbtRed * gx[x + 1][y + 1];
                    gyRed += image[row + x][col + y].rgbtRed * gy[x + 1][y + 1];
                }
            }

            int newBlue = round(sqrt(gxBlue * gxBlue + gyBlue * gyBlue));
            int newGreen = round(sqrt(gxGreen * gxGreen + gyGreen * gyGreen));
            int newRed = round(sqrt(gxRed * gxRed + gyRed * gyRed));

            tmp[row][col].rgbtBlue = (newBlue > 255) ? 255 : newBlue;
            tmp[row][col].rgbtGreen = (newGreen > 255) ? 255 : newGreen;
            tmp[row][col].rgbtRed = (newRed > 255) ? 255 : newRed;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = tmp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = tmp[i][j].rgbtGreen;
            image[i][j].rgbtRed = tmp[i][j].rgbtRed;
        }
    }

    return;
}
