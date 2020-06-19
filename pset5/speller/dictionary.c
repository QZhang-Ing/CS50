// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N] = malloc(N*sizeof(node));

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    return 0;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    // Check if dictionary founded and readable
    if (file == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        unload();
        return false;
    }
    // Prepare to load dictionary from inout file to hash table
    int index = 0, words = 0;
    char dicItem[LENGTH + 1];

    // get each word by characters
    for (int c = fgetc(file); c != EOF; c = fgetc(file))
    {
        // get every characters untill '\n' founded
        if (c != '\n')
        {
            // Append character to word
            dicItem[index] = c;
            index++;
        }
        // When a whole word founded
        else
        {
            // Terminate current word to a string
            dicItem[index] = '\0';

            // Update counter
            words++;
            // check first character of each whole word to match the hash table


            // Prepare for next word
            index = 0;
        }
    }



    return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    return false;
}

// record new word from dictionary into hash table
void newItem(char *dicItem)
{
    // Creates new node for words from dictionary
    node *n = malloc(sizefo(node));
    if (n == NULL)
    {
        return 1;
    }
    int i = 0;
    while (dicItem[i] != '\0')
    {
        n->word[i] = dicItem[i];
        i++;
    }
    // End word with \0
    n->word[i] = '\0';
    n->next = NULL;
}