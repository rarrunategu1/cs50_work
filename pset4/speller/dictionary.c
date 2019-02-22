// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

//#include "test.c"
#include "dictionary.h"

// Represents number of children for each node in a trie
#define N 27

// Represents a node in a trie
typedef struct node
{
    bool is_word;
    struct node *children[N];
}
node;

// Represents a trie
node *root;




// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize trie
    root = malloc(sizeof(node));
    node* nav = root;

    int wordCount = 0;

    if (root == NULL)
    {
        return false;
    }
    root->is_word = false;
    //each of the children initialized to NULL
    for (int i = 0; i < N; i++)
    {
        root->children[i] = NULL;
    }

    // Open dictionary TO LOAD
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    char letter;

    int letterIndex = 0;

    // ITERATES OVER THE DICTIONARY TO READ WORDS THEREIN ONE AT TIME INTO BUFFER ABOVE
    //Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {

        letter = fgetc(file);

        printf("%c\n", letter);

            if (isalpha(letter))
            {
                printf("%c\n", letter);
                printf("Hello\n");
                return tolower(letter) - 'a';
            }
            return 26;

        //PRINTS EACH WORD
        printf("%s\n", word);

        //WORD COUNT
        wordCount++;
        printf("%i\n", wordCount);


        //MAKES NEW NODE FOR A LETTER IN A WORD
        // if(nav->children[N] == NULL)
        // {
        //     node *newNode = malloc(sizeof(node));
        //     nav->children[N] = newNode;
        //     printf("This node is null.  Create node!");
        // }
         //   nav = nav->children[N];

    }


    //each element in children corresponds to a different letter

    //check value at children[i]
        //if null malloac new node for children[i] to point at
        //if not null move to new Node and continue

    //hard code check for apostrophe
    //map back to alpha
    //if at end of word, set is_word to true



    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //case-insensitive
    //should only return true for words actually in dictionary
    //beware hard coding common words like "the"
    // TODO
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    return false;
}


