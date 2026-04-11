#include "hashtable.h"

#include <stdio.h>

int main(void){
    hashTable_t hashTable;

    hashTableCtor(&hashTable);

    char testStr[10] = "hello\n";

    hashTableInsert(&hashTable, testStr);

    hashTableDtor(&hashTable);

    return 0;
}