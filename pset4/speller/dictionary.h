// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// PROTOTYPES

//to load dictionary into memory.  returns true if successful
bool load(const char *dictionary);

//returns number of words in dictionary if loaded else 0 if not loaded
unsigned int size(void);

//bool checks for word in dictionary.  returns true if yes
bool check(const char *word);

//bool to check if unload of dictionary from memory
bool unload(void);

#endif // DICTIONARY_H
