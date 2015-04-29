/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

#define LENGTH 45
#define hashTableSize 30

typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
}node;

node* hashTable[hashTableSize] = {NULL};
int dicSize = 0;

int hash_func(const char* key)
{
    // hash on the first letter of the key
    int hash = toupper(key[0]) - 'A';
    return hash;
}

/**
 * Prints a hash table's first element/all elements for each hash value.
 */
void print_func(int para)
{
    node* ptr;
    for (int i = 0; i < hashTableSize; i++)
    {
        if (hashTable[i] != NULL)
        {
            if (para == 1)
            {
                printf("hash value %i: %s \n", i, hashTable[i]->word);
            }
            else
            {
                printf("\nhash value %i: ", i);
                ptr = hashTable[i];
                while (ptr != NULL)
                {
                    printf("%s, ", ptr->word);
                    ptr = ptr->next;
                }
            }
        }        
    }
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    for (node* ptr = hashTable[hash_func(word)]; ptr != NULL; ptr = ptr->next)
    {
        if (strcasecmp(ptr->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    FILE* file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Unable to open %s\n", dictionary);
        return false;
    }
    int hword;
    while(!feof(file)){
        node* newNode = malloc(sizeof(node));
        // check if properly allocated
        if (newNode == NULL)
        {
            unload();
            fclose(file);
            return false;
        }
        // read in dictionary word by word
        if (1 == fscanf(file, "%45s", newNode->word))
        {
            hword = hash_func(newNode->word);
            if (hashTable[hword] == NULL)
            {
                hashTable[hword] = newNode;
            }
            else
            {
                newNode->next = hashTable[hword];
                hashTable[hword] = newNode;
            }
            dicSize++;
        }
        // free the node if failed to read!
        else
        {
            free(newNode);
        }
    }
    
    // check if while loop breaks out with error or not
    if (ferror(file))
    {
        unload();
        fclose(file);
        return false; 
    }
    fclose(file);
    return (dicSize > 0) ? true : false;    
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return dicSize;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    node* ptr;
    for (int i = 0; i < hashTableSize; i++)
    {
        ptr = hashTable[i];    
        while(ptr != NULL)
        {
            node* temp = ptr;
            ptr = ptr->next;
            free(temp);
        }        
    }
    free(ptr);
    return true;
}
