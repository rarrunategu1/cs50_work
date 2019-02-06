// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// PROTOTYPES

//to load dictionary
bool load(const char *dictionary);

//returns number - unsigned int
unsigned int size(void);

//bool checks for word
bool check(const char *word);

//bool to check if unload
bool unload(void);

#endif // DICTIONARY_H
