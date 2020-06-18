#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        //check if only one command line input
        printf("Wrong input argument; Usage: ./substitution key\n");
        return 1;
    }
    else
    {
        //check if length of input argument == 26
        if (strlen(argv[1]) != 26)
        {
            printf("Key must contain 26 characters\n");
            return 1;
        }
        else
        {
            //check if any non character input
            for (int i = 0; i < 26; i++)
            {    
                bool condition = ('a' <= argv[1][i] && argv[1][i] <= 'z') || ('A' <= argv[1][i] && argv[1][i] <= 'Z');
                if (!condition)
                {
                    printf("Key allows only alphabets, no numbers and no other characters are allowed.\n");
                    return 1;
                }
                else
                {
                    for (int j = 0; j < i; j++)
                    {
                        if (argv[1][j] == argv[1][i])
                        {
                            printf("duplicate alphatetical characters in the key.\n");
                            return 1;
                        }
                    }
                }
            }
        }
    }
    //plain text input
    string s = get_string("plaintext: ");
    int n = strlen(s);
    printf("ciphertext: ");
    for (int i = 0; i < n; i++)
    {
        //lower case 
        if ('a' <= s[i] && s[i] <= 'z')
        {
            int diff = s[i] - 'a';
            printf("%c", tolower(argv[1][diff]));
        }
        //upper case
        else if ('A' <= s[i] && s[i] <= 'Z')
        {
            int diff = s[i] - 'A';
            printf("%c", toupper(argv[1][diff]));
        }
        //non alphabetical characters
        else
        {
            printf("%c", s[i]);
        }
    }
    printf("\n");
    return 0;
}