#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int count_letters(string a);
int count_words(string a);
int count_sents(string a);
int grade_calcu(int l, int w, int s);

int main(void)
{
    //read input from users
    string t = get_string("Text: ");

    //count letters
    int letters = count_letters(t);
    //printf("count of letters: %i\n", letters);
    //count words
    int words = count_words(t);
    //printf("count of words: %i\n", words);
    //count sentenseces
    int sents = count_sents(t);
    //printf("count of sentensences: %i\n", sents);
    //calculation index
    int index = grade_calcu(letters, words, sents);
    if (index < 1)
    {
        printf("Before Grade 1\n");
    } 
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int count_letters(string a)
{
    int count = 0;
    for (int i = 0, n = strlen(a); i < n; i++)
    {
        if ((a[i] >= 'a' && a[i] <= 'z') || (a[i] >= 'A' && a[i] <= 'Z'))
        {
            count++;
        }
    }
    return count;
}

int count_words(string a)
{
    int count = 1;
    for (int i = 0, n = strlen(a); i < n; i++)
    {   
        char space = ' ';
        if (a[i] == space)
        {
            count++;
        }
    }
    return count;
}

int count_sents(string a)
{
    int count = 0;
    for (int i = 0, n = strlen(a); i < n; i++)
    {   
        if (a[i] == '.' || a[i] == '?' || a[i] == '!')
        {
            count++;
        }
    }
    return count;
}

int grade_calcu(int l, int w, int s)
{
    int index;
    float L = (float)l / (float)w * 100;
    float S = (float)s / (float)w * 100;
    index = round(0.0588 * L - 0.296 * S - 15.8);
    return index;
}