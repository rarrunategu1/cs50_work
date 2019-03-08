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
       //printf("%s\n", word);

       //nav->is_word = true;
       wordCount++;

        //goes through each character in every word
       for (int character = 0, wordLength = strlen(word); character < wordLength; character++)
       {
           //printf("%c\n", word[position]);

           //gets alpha index for each letter at lowercase setting
            if (isalpha(word[character]))
            {
                alphaIndex = tolower(word[character]) - 'a';
                //printf("Letter: %c\n", word[character]);
            }
            if (word[character] == '\'')
            {
            //alpha index in case there's an apostrophe.  It's a given so I don't have to give specifics on if it's an apostrophe or some other character outside of the alphabet
                alphaIndex = 26;
            }

            //ready to insert into trie
            if (nav->children[alphaIndex] == NULL)
            {
                //printf("alphaIndex: %i\n\n", alphaIndex);
                node *newNode = malloc(sizeof(node));

                //sets newNode's child to null
                for(int j = 0; j < N; j++)
                {
                    newNode->children[j] = NULL;
                }
                nav->children[alphaIndex] = newNode;
                nav = newNode;
                continue;
            }
            else
            {
                nav = nav->children[alphaIndex];

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
    return wordCount;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //case-insensitive
    //should only return true for words actually in dictionary
    //beware hard coding common words like "the"
    // TODO
    node *trav = root;
    int txtAlphaIndex = 0;


    for (int textChar = 0, textWord = strlen(word); textChar < textWord; textChar++)
    {
        //gets alpha index for each letter at lowercase setting
            if (isalpha(word[textChar]))
            {
                txtAlphaIndex = tolower(word[textChar]) - 'a';
                //printf("Letter: %c\n", word[character]);
            }
            if (word[textChar] == '\'')
            {
            //alpha index in case there's an apostrophe.  It's a given so I don't have to give specifics on if it's an apostrophe or some other character outside of the alphabet
            txtAlphaIndex = 26;
            }


            //compare to words in trie
            if(trav->children[txtAlphaIndex] == NULL)
            {
                return false;
            }
            else if (trav->children[txtAlphaIndex] != NULL && textChar != textWord -1)
            {
                trav = trav->children[txtAlphaIndex];
            }
            else if (textChar == textWord -1)
            {
                //printf("%s is a word in the dictionary.\n", word);
                return true;
            }
    }
    return false;
}
// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // // TODO
    node *cursor = root;

    //travel to last child

    if (cursor->is_word == false)
    {
        for (int position = 0; position < N; position++)
        {
            if(cursor->children[position] != NULL)
            {
                free(cursor->children[position]);
            }

        }
    }
    if (cursor != NULL)
    {
        free(cursor);
        return true;
    }
    return false;
}


