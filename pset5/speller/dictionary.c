// Implements a dictionary's functionality

#include <stdbool.h>
#include <strings.h>
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
const unsigned int N = 26 * 26;

// Hash table
node *table[N];
int wordCount = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int key = hash(word);
    node *cursor = table[key];
    //for (node *tmp = table[key]; tmp != NULL; tmp = tmp -> next)
    //{
    //    if (strcasecmp(tmp->word, word) == 0)
    //     {
    //         return true;
    //     }
    // }
    while (cursor != NULL)
    {
        // If the word is in the dictionnary
        // strcasecmp: is case-insensitive
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }

        // Set cursor to next item
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int h = 0;
    if (word[1] == '\0')
    {
        h = word[0] - 'a';
    }
    else
    {
        h = 26 * (word[0] - 'a') + (word[1] - 'a');
    }
    return h;
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
    int index = 0;
    char *dicItem = malloc(LENGTH);
    if (dicItem == NULL)
    {
        return false;
    }

    // get word by word untill EOF founded
    while (fscanf(file, "%s", dicItem) != EOF)
    {
        // insert current word as a new item into hash table
        // find hash index for the new item
        int key = hash(dicItem);
        // Creates new node for item from dictionary
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        // assign dicItem characters by characters to new item
        strcpy(n->word, dicItem);
        n->next = table[key];
        table[key] = n;
        // Track number of words in dictionary
        wordCount++;
        // Prepare for next word
        index = 0;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (wordCount > 0)
    {
        return wordCount;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
    }
    return false;
}
