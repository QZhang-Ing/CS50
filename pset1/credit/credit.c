#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    //asking user for card number
    long n;
    int count;
    n = get_long("Number ");
    count = log10(n) + 1;
    // invalid numeric input, return INVALID
    if (count != 13 && count != 16 && count != 15)
    {
        printf("INVALID\n");
        return 1;
    }
    //Check if the credit card is valid
    int digits[count];
    //Story every digits of card number in an array
    for (int i = 0; i < count; i++)
    {
        digits[i] = n % 10;
        n = n / 10;
    }
    //multiplying by 2 and store them in an new array
    int sum = 0;
    for (int i = 1; i < count; i+=2)
    {  
        int tmp = digits[i] * 2;
        sum += tmp % 10 + tmp / 10;
    }
    //add all together!
    for (int i = 0; i < count; i+=2)
    {
        sum += digits[i]; 
    }
    //check if valid
    if (sum % 10 == 0)
    {
        if (digits[count - 1] == 4)
        {
            printf("VISA\n");
        }
        else if (digits[count - 1] == 5)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("AMEX\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
    
    
}