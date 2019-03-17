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
    while(fscanf(file, "%s", word) != EOF)
    {
       //wordCount++;

        //ITERATE THROUGH EVERY LETTER IN WORD
       for (int letter = 0, wordLength = strlen(word); letter < wordLength; letter++)
       {
          //ALPHA INDEX FOR EACH LETTER
            if (isalpha(word[letter]))
            {
                alphaIndex = tolower(word[letter]) - 'a';
            }
            else if (word[letter] == '\'')
            {
                alphaIndex = 26;
            }

            //INSERT WORDS INTO TRIE IF EQUAL TO NULL
            if (nav->children[alphaIndex] == NULL)
            {
                node *newNode = calloc(1, sizeof(node));

                //SET NEW NODE CHILD TO NULL
                for(int j = 0; j < N; j++)
                {
                    newNode->children[j] = NULL;
                }

                nav->children[alphaIndex] = newNode;
                nav = newNode;
            }
            else
            {
                //TRAVELS THROUGH TRIE IF NOT EQUAL TO NULL
                nav = nav->children[alphaIndex];
            }
       }
        wordCount++;
        nav->is_word = true;
        nav = root;
    }

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

        //ALPHA INDEX FOR EACH LETTER
        if (isalpha(word[textLetter]))
        {
            txtAlphaIndex = tolower(word[textLetter]) - 'a';
            //printf("Letter: %c\n", word[character]);
        }
        else if (word[textLetter] == '\'')
        {
            txtAlphaIndex = 26;
        }

        //SEE IF WORD IN TXT FILE EXISTS IN THE TRIE
        if(trav->children[txtAlphaIndex] == NULL)
        {
            //misspelledWord++;
            return false;
        }
        else if (trav->children[txtAlphaIndex] != NULL)
        {
            trav = trav->children[txtAlphaIndex];
        }
    }
    return trav->is_word;
}

//recursive function to use in unload
void freeNode(node *trav)
{
    for (int i = 0; i < N; i++)
    {
        // Pointer set to children
        if (trav->children[i])
        {
            freeNode(trav->children[i]);
        }
    }
    free(trav);
}
// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    freeNode(root);
    return true;
}




