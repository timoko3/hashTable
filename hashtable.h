#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "cashFriendlyList/list.h"

#include <stddef.h>

typedef unsigned long (*hashFunction_t) (char* str);

struct hashTableCell_t{
    list_t value;
    int   hash;
};

struct hashTable_t{
    size_t           size;
    size_t           amountElements;
    hashFunction_t   hashFunction;
    hashTableCell_t* cells;
};

bool hashTableCtor(hashTable_t* hashTable);
bool hashTableInsert(hashTable_t* hashTable, char* str);
bool hashTableDtor(hashTable_t* hashTable);

#endif /* HASH_TABLE_H */