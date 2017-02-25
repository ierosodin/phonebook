#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "phonebook_hash.h"

/* FILL YOUR OWN IMPLEMENTATION HERE! */
entry *findName(char lastName[], entry *pHead[])
{
    unsigned int n = BKDRHash(lastName);
    n %= SIZE;
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

entry *append(char lastName[], entry *e)
{
    /* allocate memory for the new entry and put lastName */
    e->pNext = (entry *) malloc(sizeof(entry));
    e = e->pNext;
    strcpy(e->lastName, lastName);
    e->pNext = NULL;
    return e;
}

unsigned int BKDRHash(char lastName[])
{
    unsigned int seed = 131;
    unsigned int hash = 0;
    int i = 0;
    while (i < strlen(lastName)) {
        hash = hash * seed + lastName[i];
        i++;
    }
    return (hash & 0x7FFFFFFF) % SIZE;
}

unsigned int ELFHash(char lastName[])
{
    unsigned int hash = 0;
    unsigned int x    = 0;

    int i = 0;
    while (i < strlen(lastName)) {
        hash = (hash << 4) + lastName[i];
        if ((x = hash & 0xF0000000L) != 0) {
            hash ^= (x >> 24);
            hash &= ~x;
        }
        i++;
    }

    return (hash & 0x7FFFFFFF) % SIZE;
}

unsigned int PJWHash(char lastName[])
{
    unsigned int BitsInUnignedInt = (unsigned int)(sizeof(unsigned int) * 8);
    unsigned int ThreeQuarters    = (unsigned int)((BitsInUnignedInt  * 3) / 4);
    unsigned int OneEighth        = (unsigned int)(BitsInUnignedInt / 8);
    unsigned int HighBits         = (unsigned int)(0xFFFFFFFF) << (BitsInUnignedInt - OneEighth);
    unsigned int hash             = 0;
    unsigned int test             = 0;

    int i = 0;
    while (i < strlen(lastName)) {
        hash = (hash << OneEighth) + lastName[i];
        if ((test = hash & HighBits) != 0) {
            hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
        }
        i++;
    }

    return (hash & 0x7FFFFFFF) % SIZE;
}

unsigned int APHash(char lastName[])
{
    unsigned int hash = 0;
    int i = 0;

    while (i < strlen(lastName)) {
        if ((i & 1) == 0) {
            hash ^= ((hash << 7) ^ lastName[i] ^ (hash >> 3));
        } else {
            hash ^= (~((hash << 11) ^ lastName[i] ^ (hash >> 5)));
        }
        i++;
    }

    return (hash & 0x7FFFFFFF) % SIZE;
}

unsigned int SDBMHash(char lastName[])
{
    unsigned int hash = 0;

    int i = 0;
    while (i < strlen(lastName)) {
        // equivalent to: hash = 65599*hash + (*str++);
        hash = lastName[i] + (hash << 6) + (hash << 16) - hash;
        i++;
    }

    return (hash & 0x7FFFFFFF) % SIZE;
}

unsigned int RSHash(char lastName[])
{
    unsigned int b = 378551;
    unsigned int a = 63689;
    unsigned int hash = 0;

    int i = 0;
    while (i < strlen(lastName)) {
        hash = hash * a + lastName[i];
        a *= b;
        i++;
    }

    return (hash & 0x7FFFFFFF) % SIZE;
}

unsigned int JSHash(char lastName[])
{
    unsigned int hash = 1315423911;

    int i = 0;
    while (i < strlen(lastName)) {
        hash ^= ((hash << 5) + lastName[i] + (hash >> 2));
        i++;
    }

    return (hash & 0x7FFFFFFF) % SIZE;
}

void free_list(entry *e)
{
    entry *tmp;
    while ((tmp = e) != NULL) {
        e = e->pNext;
        free(tmp);
    }
}
