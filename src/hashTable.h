#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "cashFriendlyList/list.h"

#include <stddef.h>

typedef unsigned long hash_t;
typedef const char* hashTableData_t; // int double

typedef unsigned long (*hashFunction_t) (char* str);

struct hashTableCell_t{
    list_t value;
};

struct hashTable_t{
    size_t           size; // nCells / capacity
    size_t           amountElements; // unique and duplicate
    hashFunction_t   hashFunction;
    hashTableCell_t* cells;
};

bool hashTableCtor(hashTable_t* hashTable);
bool hashTableInsert(hashTable_t* hashTable, char* str);
bool hashTableFind(hashTable_t* hashTable, char* str, int* findCellNum);
bool hashTableDtor(hashTable_t* hashTable);


#endif /* HASH_TABLE_H */