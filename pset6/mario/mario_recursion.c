#include <stdio.h>
#include <cs50.h>

void draw(int h, int H);

int main(void)
{
    // Get height of pyramid from the user
    int height = get_int("Height: ");
    // extra variable to store height as a fix value
    int maxHeight = height;
    // Draw pyramid
    draw(height, maxHeight);
}

void draw(int h, int H)
{
    // condition to stop recursion
    if (h == 0)
    {
        return;
    }

    // Draw pyramid of height h - 1
    draw(h - 1, H);

    // Draw the row of height h
    // Draw spaces at the beginning of each row
    int j = H - h;
    while (j != 0)
    {
        printf(" ");
        j--;
    }
    // Draw #s and the 2 spaces in the middle
    for (int i = 0; i < h; i++)
    {
        printf("#");
    }
    printf("  ");
    for (int i = 0; i < h; i++)
    {
        printf("#");
    }
    printf("\n");
}