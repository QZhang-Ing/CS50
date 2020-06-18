#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //asking input and check if the input integer is valid
    int n;
    do
    {
        n = get_int("Height: ");
    } 
    while (n <= 0 || n > 8);
    
    for (int i = 0; i < n; i++)
    {
        //print the space on the left side
        for (int j = 0; j < n - i - 1; j++)
        {
            printf(" ");
        }
        //print the # on the left side
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }
        //print space in the middle
        printf("  ");
        //print the # on the right side
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}