#include "hashtable.h"
#include "DSL.h"

#include <malloc.h>
#include <assert.h>

const size_t HASH_TABLE_SIZE_C            = 100; 
// const size_t HASH_TABLE_AMOUNT_ELEMENTS_C = 50;

int basicHashFunction(char* str);

bool hashTableCtor(hashTable_t* hashTable){
    HASH_TABLE_SIZE(hashTable)            = HASH_TABLE_SIZE_C; 
    HASH_TABLE_AMOUNT_ELEMENTS(hashTable) = 0; 
    HASH_TABLE_FUNCTION(hashTable)        = basicHashFunction;

    HASH_TABLE_CELLS(hashTable)           = (hashTableCell_t*) calloc(HASH_TABLE_SIZE_C, sizeof(hashTableCell_t));
    assert(HASH_TABLE_CELLS(hashTable));

    return true;
}

bool hashTableAdd(hashTable_t* hashTable, char* str){
    assert(hashTable);
    assert(str);

    size_t cellNumber = HASH_TABLE_FUNCTION(hashTable) (str);

    hashTableCell_t curCell = HASH_TABLE_CELLS(hashTable)[cellNumber];
    
    

    return true;
}

bool hashTableDtor(hashTable_t* hashTable){
    free(HASH_TABLE_CELLS(hashTable));         

    return true;
}

int basicHashFunction(char* str){
    assert(str);

    return 0;
}