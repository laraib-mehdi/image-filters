#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int average = (image[row][col].rgbtRed + image[row][col].rgbtBlue + image[row][col].rgbtGreen) / 3.0 + 0.5;
            image[row][col].rgbtGreen = image[row][col].rgbtRed = image[row][col].rgbtBlue = average;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE img[height][width];
    for (int row = 0; row < height; row ++)
    {
        for (int col = 0; col < width; col ++)
        {
            img[row][col] = image[row][col];
        }
    }
    for (int row = 0; row < height; row++){
        for (int col = 0,swap = width - 1; col < width; col++)
        {
            image[row][col] = img[row][swap];
            swap--;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE img[height][width];
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            img[row][col] = image[row][col];
        }
    }

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            float totalr = 0, totalg = 0, totalb = 0;
            int count = 0;

            for (int rows = row - 1; rows <= row + 1; rows++)
            {
                for (int cols = col - 1; cols <= col + 1; cols++)
                {
                    if (rows >= 0 && rows < height && cols >= 0 && cols < width)
                    {
                        totalr += img[rows][cols].rgbtRed;
                        totalg += img[rows][cols].rgbtGreen;
                        totalb += img[rows][cols].rgbtBlue;
                        count++;
                    }
                }
            }

            image[row][col].rgbtRed = round(totalr / count);
            image[row][col].rgbtGreen = round(totalg / count);
            image[row][col].rgbtBlue = round(totalb / count);
        }
    }
}
// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE img[height][width];
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            img[row][col] = image[row][col];
        }
    }

    int gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int gy[3][3] = {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int mrow[3] = {row-1, row, row+1};
            int mcol[3] = {col-1, col, col+1};
            int gxRed = 0, gxGreen = 0, gxBlue = 0;
            int gyRed = 0, gyGreen = 0, gyBlue = 0;

            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    int nrow = mrow[i];
                    int ncol = mcol[j];
                    RGBTRIPLE pixel = img[nrow][ncol];

                    if(nrow<height && nrow >= 0 && ncol<width && ncol>=0)
                    {
                    gxRed += pixel.rgbtRed * gx[i][j];
                    gxGreen += pixel.rgbtGreen * gx[i][j];
                    gxBlue += pixel.rgbtBlue * gx[i][j];

                    gyRed += pixel.rgbtRed * gy[i][j];
                    gyGreen += pixel.rgbtGreen * gy[i][j];
                    gyBlue += pixel.rgbtBlue * gy[i][j];
                    }
                }
            }

            int magnitudeRed = round(sqrt(pow(gxRed, 2) + pow(gyRed, 2)));
            int magnitudeGreen = round(sqrt(pow(gxGreen, 2) + pow(gyGreen, 2)));
            int magnitudeBlue = round(sqrt(pow(gxBlue, 2) + pow(gyBlue, 2)));

            image[row][col].rgbtRed = (magnitudeRed > 255) ? 255 : magnitudeRed;;
            image[row][col].rgbtGreen = (magnitudeGreen > 255) ? 255 : magnitudeGreen;;
            image[row][col].rgbtBlue = (magnitudeBlue > 255) ? 255 : magnitudeBlue;;
        }
    }
}
