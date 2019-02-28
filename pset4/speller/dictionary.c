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

int wordCount = 0;



// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize trie
    root = malloc(sizeof(node));
    node* nav = root;

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

    int index = 0;

    int alphaIndex;

    // ITERATES OVER THE DICTIONARY TO READ WORDS THEREIN ONE AT TIME INTO BUFFER ABOVE
    //Insert words into trie
    while(fscanf(file, "%s", word) != EOF)
    {
       printf("%s\n", word);

       nav->is_word = true;
       wordCount++;

        //goes through each character in every word
       for(int character = 0, wordLength = strlen(word); character < wordLength; character++)
       {
           //printf("%c\n", word[position]);

           //gets alpha index for each letter at lowercase setting
           if (isalpha(word[character]))
           {
               alphaIndex = tolower(word[character]) - 'a';
               printf("Letter: %c alphaIndex: %i\n", word[character], alphaIndex);
           }
           else if (word[character])
           {
           //alpha index in case there's an apostrophe.  It's a given so I don't have to give specifics on if it's an apostrophe or some other character outside of the alphabet
           alphaIndex = 26;
           }


        //ready to insert into trie
         if (nav->children[alphaIndex] == NULL)
        {
            printf("alphaIndex: %i\n", alphaIndex);
            node *newNode = malloc(sizeof(node));

            nav->children[alphaIndex] = newNode;

            //sets newNode's child to null
            for(int j = 0; j < N; j++)
            {
                newNode->children[j] = NULL;
            }

            nav = newNode;

            if(nav->children[alphaIndex] == NULL)
            {
                printf("Hello\n");
            }
            continue;
        }
        else
        {
            nav = nav->children[alphaIndex];
            continue;
        }
}


    }

    //if at end of word, set is_word to true
    // nav->is_word = true;
    // wordCount++;
    printf("WordCount %i\n", wordCount);

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return wordCount;
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


