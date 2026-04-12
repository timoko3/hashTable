#include "hashTable.h"
#include "DSL.h"

// #define DEBUG
#include "general/debug.h"

#include <malloc.h>
#include <assert.h>
#include <string.h>

const size_t HASH_TABLE_SIZE_C            = 100; 
// const size_t HASH_TABLE_AMOUNT_ELEMENTS_C = 50;

const int SEARCH_NOT_FOUND_VALUE          = -1;

unsigned long gnuHash(char* str);

bool hashTableCtor(hashTable_t* hashTable){
    HASH_TABLE_SIZE(hashTable)            = HASH_TABLE_SIZE_C; 
    HASH_TABLE_AMOUNT_ELEMENTS(hashTable) = 0; 
    HASH_TABLE_FUNCTION(hashTable)        = gnuHash;

    HASH_TABLE_CELLS(hashTable)           = (hashTableCell_t*) calloc(HASH_TABLE_SIZE_C, sizeof(hashTableCell_t));

    for(size_t i = 0; i < HASH_TABLE_SIZE_C; i++){
        HASH_TABLE_CELLS(hashTable)[i].value.capacity = 3;
        listCtor(&HASH_TABLE_CELLS(hashTable)[i].value);
    }

    assert(HASH_TABLE_CELLS(hashTable));

    return true;
}

bool hashTableInsert(hashTable_t* hashTable, char* str){
    assert(hashTable);
    assert(str);

    size_t cellNumber = HASH_TABLE_FUNCTION(hashTable) (str);

    LPRINTF("cellNumber = %llu", cellNumber);

    hashTableCell_t* curCell = &(HASH_TABLE_CELLS(hashTable)[cellNumber]);
    
    // check exists word
    int findCellNum = 0;
    hashTableFind(hashTable, str, &findCellNum);
    if(!(findCellNum == SEARCH_NOT_FOUND_VALUE)) return false;

    listInsertToTail(&HASH_TABLE_CELL_VALUE(curCell), str);

    HASH_TABLE_AMOUNT_ELEMENTS(hashTable)++;

    LPRINTF("addrListInsFunc = %p", &curCell);

    LPRINTF("size = %llu\n", HASH_TABLE_CELL_VALUE(curCell).size);

    return true;
}

bool hashTableFind(hashTable_t* hashTable, char* str, int* findCellNum){
    assert(hashTable);
    assert(str);

    *findCellNum = SEARCH_NOT_FOUND_VALUE;

    size_t cellNumber = HASH_TABLE_FUNCTION(hashTable) (str);

    LPRINTF("cellNumber = %llu", cellNumber);

    hashTableCell_t* curCell = &(HASH_TABLE_CELLS(hashTable)[cellNumber]);

    LPRINTF("addrListFindFunc = %p", curCell);

    int curElem = *head(&HASH_TABLE_CELL_VALUE(curCell));
    LPRINTF("size = %llu\n", HASH_TABLE_CELL_VALUE(curCell).size);
    for(size_t i = 0; i < HASH_TABLE_CELL_VALUE(curCell).size; i++){
        if(!strcmp(str, *data(&HASH_TABLE_CELL_VALUE(curCell), curElem))){
            *findCellNum = cellNumber;
            break; 
        }
        
        curElem = *next(&HASH_TABLE_CELL_VALUE(curCell), curElem);
    }

    return true;
}

bool hashTableDtor(hashTable_t* hashTable){
    for(size_t i = 0; i < HASH_TABLE_SIZE_C; i++){
        listDtor(&HASH_TABLE_CELLS(hashTable)[i].value);
    }

    free(HASH_TABLE_CELLS(hashTable));         

    return true;
}

unsigned long gnuHash(char* str){
    assert(str);

    unsigned long hash = 5381;

    for (unsigned char c = *str; c != '\0'; c = *++str) {
        hash = (hash << 5) + hash + c; // h * 33 + c
    }

    return hash % HASH_TABLE_SIZE_C;
}

