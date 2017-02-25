#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "phonebook_hash.h"

/* FILL YOUR OWN IMPLEMENTATION HERE! */
entry *findName(char lastName[], entry *pHead[])
{
    unsigned int n = hashFunc(lastName);
    entry *tmp;
    if (pHead[n]->pNext)
        tmp = pHead[n]->pNext;
    else
        return NULL;
    while (tmp) {
        if (strcasecmp(lastName, tmp->lastName) == 0)
            return tmp;
        tmp = tmp->pNext;
    }
    return NULL;
}

void append(char lastName[], entry *e[])
{
    /* allocate memory for the new entry and put lastName */
    unsigned int n = hashFunc(lastName);
    e[n]->pNext = (entry *) malloc(sizeof(entry));
    e[n] = e[n]->pNext;
    strcpy(e[n]->lastName, lastName);
    e[n]->pNext = NULL;
}

unsigned int hashFunc(char lastName[])
{
    unsigned int seed = 31;
    unsigned int hash_number = 0;
    int i = 0;
    while (i < strlen(lastName)) {
        hash_number = hash_number * seed + lastName[i];
        ++i;
    }
    return hash_number %= SIZE;
}

void free_list(entry *e)
{
    entry *tmp;
    while ((tmp = e) != NULL) {
        e = e->pNext;
        free(tmp);
    }
}