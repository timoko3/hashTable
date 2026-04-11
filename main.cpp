#include "hashtable.h"

#include <stdio.h>

int main(void){
    hashTable_t hashTable;

    hashTableCtor(&hashTable);

    char testStr[10] = "hello\n";

    hashTableInsert(&hashTable, testStr);

    for(size_t i = 0; i < hashTable.size; i++){
        listGraphDump(&hashTable.cells[i].value);
    }

    hashTableDtor(&hashTable);

    return 0;
}