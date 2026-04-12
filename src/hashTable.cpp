#include "hashTable.h"
#include "DSL.h"

// #define DEBUG
#include "general/debug.h"

#include <malloc.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>

const size_t HASH_TABLE_SIZE_C            = 4000; 
// const size_t HASH_TABLE_AMOUNT_ELEMENTS_C = 50;

const int SEARCH_NOT_FOUND_VALUE          = -1;

unsigned long constHash(char* str);
unsigned long lenHash(char* str);
unsigned long firstSymHash(char* str);
unsigned long sumHash(char* str);
unsigned long gnuHash(char* str);
unsigned long crcHash(char* str);
unsigned long rollHash(char* str);
unsigned long murMurHash(char* str);

bool hashTableCtor(hashTable_t* hashTable){
    HASH_TABLE_SIZE(hashTable)            = HASH_TABLE_SIZE_C; 
    HASH_TABLE_AMOUNT_ELEMENTS(hashTable) = 0; 
    HASH_TABLE_FUNCTION(hashTable)        = murMurHash;

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

unsigned long constHash(char* str){
    assert(str);
    
    return 0;
}

unsigned long lenHash(char* str){
    assert(str);

    return strlen(str);
}

unsigned long firstSymHash(char* str){
    assert(str);

    return *str % HASH_TABLE_SIZE_C;
}

unsigned long sumHash(char* str){
    assert(str);

    unsigned long sum = 0;
    for(size_t i = 0; i < strlen(str); i++){
        sum += (unsigned long) str[i];
    }

    return sum % HASH_TABLE_SIZE_C;
}

unsigned long gnuHash(char* str){
    assert(str);

    unsigned long hash = 5381;

    for (unsigned char c = *str; c != '\0'; c = *++str) {
        hash = (hash << 5) + hash + c; // h * 33 + c
    }

    return hash % HASH_TABLE_SIZE_C;
}

unsigned long crcHash(char* str){
    assert(str);

    uint32_t crc = 0xFFFFFFFF;

    for (size_t i = 0; i < strlen(str); i++) {
        crc ^= str[i];

        for(int j = 0; j < 8; j++){
            if(crc & 1){
                crc = (crc >> 1) ^ 0xEDB88320;
            }
            else{
                crc >>= 1;
            }
        }
    }

    return (unsigned long) (~crc % HASH_TABLE_SIZE_C);
}

unsigned long rollHash(char* str){
    assert(str);

    uint32_t hash = 0;

    for (size_t i = 0; i < strlen(str); i++){
        hash = (hash << 5) | (hash >> 27);    
        hash ^= str[i];
    }
    
    return (unsigned long) (hash % HASH_TABLE_SIZE_C);
}

unsigned long murMurHash(char* str){
    assert(str);

    uint32_t hash = 0;
    uint32_t c1   = 0xcc9e2d51;
    uint32_t c2   = 0x1b873593;

    int len       = strlen(str);

    for(size_t i = 0; i < len; i++){
        uint32_t k = str[i];

        k *= c1;
        k = (k << 15) | (k >> 17);
        k *= c2;

        hash ^= k;
        hash = (hash << 13) | (hash >> 19);
        hash = hash * 5 + 0xe6546b64;
    }

    hash ^= len;
    hash ^= hash >> 16;
    hash *= 0x85ebca6b;
    hash ^= hash >> 13;
    hash *= 0xc2b2ae35;
    hash ^= hash >> 16;

    return (unsigned long) hash % HASH_TABLE_SIZE_C; 
}