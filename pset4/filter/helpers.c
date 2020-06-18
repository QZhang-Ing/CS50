#include "helpers.h"
#include <math.h>

int maxCheck(int a);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int greyValue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            greyValue = round((image[i][j].rgbtBlue
                               + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtGreen = greyValue;
            image[i][j].rgbtRed = greyValue;
            image[i][j].rgbtBlue = greyValue;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaRed;
    float sepiaGreen;
    float sepiaBlue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // converts integer to float
            float tempRed = (float)image[i][j].rgbtRed;
            float tempGreen = (float)image[i][j].rgbtGreen;
            float tempBlue = (float)image[i][j].rgbtBlue;

            sepiaRed = round(0.393 * tempRed + 0.769 * tempGreen
                             + 0.189 * tempBlue);
            sepiaGreen = round(0.349 * tempRed + 0.686 * tempGreen
                               + 0.168 * tempBlue);
            sepiaBlue = round(0.272 * tempRed + 0.534 * tempGreen
                              + 0.131 * tempBlue);

            // result can not be larger than 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][width - j - 1];
            image[i][width - j - 1]= image[i][j];
            image[i][j] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int sumGreen;
    int sumRed;
    int sumBlue;
    float count;
    // creats unchanged image to loop through
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sumGreen = 0;
            sumRed = 0;
            sumBlue = 0;
            count = 0.00;
            //if pixel is not on the first line and last line, means add three neighbors (i-1, i, i+1)
            for (int k = -1; k < 2; k++)
            {
                if (i + k < 0 || i + k > height - 1)
                {
                    // jump out of the this for loop
                    continue;
                }
                //if pixel is not on the first colume and last colume
                for (int h = -1; h < 2; h++)
                {
                    if (j + h < 0 || j + h > width - 1)
                    {
                        // jump out of this loop
                        continue;
                    }

                    sumGreen += image[i + k][j + h].rgbtGreen;
                    sumRed += image[i + k][j + h].rgbtRed;
                    sumBlue += image[i + k][j + h].rgbtBlue;
                    count++;
                }
            }
            temp[i][j].rgbtBlue = round(sumBlue / count);
            temp[i][j].rgbtGreen = round(sumGreen / count);
            temp[i][j].rgbtRed = round(sumRed / count);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }

}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // sobel filters
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // creates copied image to story the original image and extra lines/columes
    // of black pixels to loop through
    RGBTRIPLE temp[height + 2][width + 2];
    for (int i = 0; i < height + 2; i++)
    {
        for (int j = 0; j < width + 2; j++)
        {
            if (i == 0 || j == 0 || i == height + 1 || j == width + 1)
            {
                temp[i][j].rgbtRed = 0;
                temp[i][j].rgbtGreen = 0;
                temp[i][j].rgbtBlue = 0;
            }
            else
            {
                temp[i][j] = image[i - 1][j - 1];
            }
        }
    }
    // second copied image with extra black pixels to story the result
    RGBTRIPLE temp2[height + 2][width + 2];
    for (int i = 0; i < height + 2; i++)
    {
        for (int j = 0; j < width + 2; j++)
        {
            temp2[i][j] = temp[i][j];
        }
    }

    //calculation based on the copied image
    for (int i = 1; i < height + 1; i++)
    {

        for (int j = 1; j < width + 1; j++)
        {
            // varibles to stroy Gx Gy for each color channels
            float blueGx = 0.0, redGx = 0.0, greenGx = 0.0;
            float blueGy = 0.0, redGy = 0.0, greenGy = 0.0;

            for (int k = -1; k < 2; k++)
            {
                for (int h = -1; h < 2; h++)
                {
                    //calculate the Gx for each R G B channel by using temp
                    blueGx += temp[i + k][j + h].rgbtBlue * Gx[k + 1][h + 1];
                    redGx += temp[i  + k][j + h].rgbtRed * Gx[k + 1][h + 1];
                    greenGx += temp[i + k][j + h].rgbtGreen * Gx[k + 1][h + 1];
                    //calculate the Gy for each R G B channel by using temp
                    blueGy += temp[i + k][j + h].rgbtBlue * Gy[k + 1][h + 1];
                    redGy += temp[i + k][j + h].rgbtRed * Gy[k + 1][h + 1];
                    greenGy += temp[i + k][j + h].rgbtGreen * Gy[k + 1][h + 1];
                }
            }
            //store result for each pixels (i, j) in temp2
            temp2[i][j].rgbtRed = maxCheck(round(sqrt(redGx * redGx + redGy * redGy)));
            temp2[i][j].rgbtBlue = maxCheck(round(sqrt(blueGx * blueGx + blueGy * blueGy)));
            temp2[i][j].rgbtGreen = maxCheck(round(sqrt(greenGx * greenGx + greenGy * greenGy)));
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp2[i + 1][j + 1];
        }
    }
}

// cap rgb value to 255
int maxCheck(int a)
{
    if (a > 255)
    {
        a = 255;
    }
    return a;
}