#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16

/* TODO: After modifying the original version, uncomment the following
 * line to set OPT properly */
#define MPOOL 1
#define SIZE 3571
typedef struct __PHONE_BOOK_INFO {
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
} info;

typedef struct __PHONE_BOOK_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    struct __PHONE_BOOK_INFO *info;
    struct __PHONE_BOOK_ENTRY *pNext;
} entry;

void create_m_pool(int size);
void free_m_pool(void);
entry *findName(char lastName[], entry *pHead[]);
entry *append(char lastName[], entry *e);
unsigned int hashFunc(char *str);
void free_list(entry *e);
#endif
