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

    int alphaIndex = 0;


    // ITERATES OVER THE DICTIONARY TO READ WORDS THEREIN ONE AT TIME INTO BUFFER ABOVE
    //Insert words into trie
    while(fscanf(file, "%s", word) != EOF)
    {
       wordCount++;

        //goes through each character in every word
       for (int letter = 0, wordLength = strlen(word); letter < wordLength; letter++)
       {
           //printf("%c\n", word[position]);

           //gets alpha index for each letter at lowercase setting
            if (isalpha(word[letter]))
            {
                alphaIndex = tolower(word[letter]) - 'a';
                //printf("Letter: %c\n", word[character]);
            }
            else if (word[letter] == '\'')
            {
            //alpha index in case there's an apostrophe.  It's a given so I don't have to give specifics on if it's an apostrophe or some other character outside of the alphabet
                alphaIndex = 26;
            }

            if (nav->children[alphaIndex] != NULL)
            {
                //printf("Hello");
                nav = nav->children[alphaIndex];
            }
            //ready to insert into trie
            else if (nav->children[alphaIndex] == NULL)
            {
                //printf("Hello");
                node *newNode = malloc(sizeof(node));
                nav->children[alphaIndex] = newNode;

                //sets newNode's child to null
                for(int j = 0; j < N; j++)
                {
                    newNode->children[j] = NULL;
                }
                //printf("alphaIndex: %i\n\n", alphaIndex);
                nav = newNode;
            }
       }

        nav->is_word = true;
        nav = root;
    }

    //printf("WordCount %i\n", wordCount);

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (&load)
    {
        return wordCount;
    }

    return 0;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *trav = root;

    int misspelledWord = 0;

    for (int textLetter = 0, textWord = strlen(word); textLetter < textWord; textLetter++)
    {
        int txtAlphaIndex = 0;
        //gets alpha index for each letter at lowercase setting
        if (isalpha(word[textLetter]))
        {
            txtAlphaIndex = tolower(word[textLetter]) - 'a';
            //printf("Letter: %c\n", word[character]);
        }
        else if (word[textLetter] == '\'')
        {
        //alpha index in case there's an apostrophe.  It's a given so I don't have to give specifics on if it's an apostrophe or some other character outside of the alphabet
        txtAlphaIndex = 26;
        }


        //compare to words in trie
        if(trav->children[txtAlphaIndex] == NULL)
        {
            misspelledWord++;
            return false;
        }
        else if (trav->children[txtAlphaIndex] != NULL)
        {
            trav = trav->children[txtAlphaIndex];
        }
    }
    return trav->is_word;
}

//recursie function to use in unload
void freeNode(node *trav)
{
    for (int i = 0; i < N; i++)
    {
        // Pointer set to children
        if (trav -> children[i])
            freeNode(trav -> children[i]);

    }
    free(trav);
}
// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    freeNode(root);
    return true;
}




