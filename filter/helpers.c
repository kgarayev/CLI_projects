#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float average;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;

            image[i][j].rgbtBlue = round(average);
            image[i][j].rgbtGreen = round(average);
            image[i][j].rgbtRed = round(average);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE temp;

    int left = 0;
    int iseven = width % 2;

    if (iseven == 0)
    {
        for (int i = 0; i < height; i++)
        {
            int right = width - 1;

            for (left = 0; left < (width / 2); left++)
            {
                temp = image[i][left];
                image[i][left] = image[i][right];
                image[i][right] = temp;

                right--;
            }
        }
    }
    else
    {
        for (int i = 0; i < height; i++)
        {
            int right = width - 1;

            for (left = 0; left <= (width / 2); left++)
            {
                temp = image[i][left];
                image[i][left] = image[i][right];
                image[i][right] = temp;

                right--;
            }
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width; j++)
        {

            int count = 0;
            int rowCoords[] = {i - 1, i, i + 1};
            int colCoords[] = {j - 1, j, j + 1};

            float Rtotal = 0, Gtotal = 0, Btotal = 0;

            for ( int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    int curRow = rowCoords[k];
                    int curCol = colCoords[l];

                    if (curRow >= 0 && curRow < height && curCol >= 0 && curCol < width)
                    {
                        RGBTRIPLE pixel = image[curRow][curCol];

                        Rtotal += pixel.rgbtRed;
                        Btotal += pixel.rgbtBlue;
                        Gtotal += pixel.rgbtGreen;

                        count++;
                    }


                }

            }

            temp[i][j].rgbtRed = round(Rtotal / count);
            temp[i][j].rgbtBlue = round(Btotal / count);
            temp[i][j].rgbtGreen = round(Gtotal / count);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }


    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE temp[height][width];

    int kernelx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}};

    int kernely[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width; j++)
        {
            int rowCoords[] = {i - 1, i, i + 1};
            int colCoords[] = {j - 1, j, j + 1};

            float Gxblue = 0;
            float Gxred = 0;
            float Gxgreen = 0;
            float Gyred = 0;
            float Gygreen = 0;
            float Gyblue = 0;

            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    int curRow = rowCoords[k];
                    int curCol = rowCoords[l];

                    if (curRow >= 0 && curRow < height && curCol >= 0 && curCol < width)
                    {
                        RGBTRIPLE pixel = image[curRow][curCol];

                        Gxred += pixel.rgbtRed * kernelx[k][l];
                        Gxblue += pixel.rgbtBlue * kernelx[k][l];
                        Gxgreen += pixel.rgbtGreen * kernelx[k][l];

                        Gyred += pixel.rgbtRed * kernely[k][l];
                        Gyblue += pixel.rgbtBlue * kernely[k][l];
                        Gygreen += pixel.rgbtGreen * kernely[k][l];

                    }
                }
            }

            int rootred = round(sqrt(Gxred * Gxred + Gyred * Gyred));
            int rootblue = round(sqrt(Gxblue * Gxblue + Gyblue * Gyblue));
            int rootgreen = round(sqrt(Gxgreen * Gxgreen + Gygreen * Gygreen));

            temp[i][j].rgbtRed = rootred > 255 ? 255 : rootred;
            temp[i][j].rgbtBlue = rootblue > 255 ? 255 : rootblue;
            temp[i][j].rgbtGreen = rootgreen > 255 ? 255 : rootgreen;

        }

    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }


    return;

}

