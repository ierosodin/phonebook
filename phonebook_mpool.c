#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "phonebook_mpool.h"
#include "memorypool.h"

static m_pool *pool = NULL;

/* FILL YOUR OWN IMPLEMENTATION HERE! */
void create_m_pool(int size)
{
    pool = pool_allocate(size);
}

void free_m_pool(void)
{
    pool_free(pool);
}

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

entry *append(char lastName[], entry *e)
{
    /* allocate memory for the new entry and put lastName */
    e->pNext = (entry *) pool_access(pool, sizeof(entry));
    e = e->pNext;
    strcpy(e->lastName, lastName);
    e->pNext = NULL;
    return e;
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
