#include "hashtable.h"
#include "DSL.h"

#include "general/debug.h"
#include "general/file.h"

#include "measures/handler.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <malloc.h>
#include <stdlib.h>

const size_t MAX_FILE_NAME_LENGTH = 64;
const size_t N_SEARCH             = 10e7; 
const size_t N_TESTS              = 1;

void testHashTable(words_t* words, size_t nSearches);

int main(int argc, char* argv[]){
    char wordsFileName[MAX_FILE_NAME_LENGTH] = "";
    size_t nSearches = N_SEARCH;
    if(argc >= 3){
        if(!strcmp("-f", argv[1])){
            strcpy(wordsFileName, argv[2]);
        }

        if(argc == 5 && !strcmp("-n", argv[3])){
            nSearches = atoi(argv[4]);
        }

        else{
            printf("incorrect option\n");
        }
    }

    fileDescription wordsFileDesc = {
        wordsFileName,
        "rb"
    };
    FILE*  wordsFilePtr     = myOpenFile(&wordsFileDesc);
    assert(wordsFilePtr);

    size_t wordsFileSize    = getFileSize(wordsFileName);

    char* wordsBuffer = getTextToBuffer(wordsFilePtr, wordsFileSize);
    
    LPRINTF("buffer = %s, bufferSize = %llu", wordsBuffer, wordsFileSize);

    words_t words = divideBufferToWords(wordsBuffer, wordsFileSize);

    for(size_t i = 0; i < N_TESTS; i++){
        testHashTable(&words, nSearches);
    }

    // dumpWords(&words);

    // free Words strcut
    free(wordsBuffer);
    free(words.ptrs);

    return 0;
}

void testHashTable(words_t* words, size_t nSearches){
    assert(words);

    hashTable_t hashTable;
    hashTableCtor(&hashTable);

    // char testStr[10] = "hello\n";

    for(size_t curWord = 0; curWord < words->count; curWord++){
        hashTableInsert(&hashTable, words->ptrs[curWord].ptr);
    }

    // // for(size_t i = 0; i < HASH_TABLE_CAPACITY((&hashTable)); i++){
    // //     listGraphDump(&hashTable.cells[i].value);
    // // }

    // int* cellNumber       = (int*) calloc(HASH_TABLE_CAPACITY((&hashTable)), sizeof(int));
    // assert(cellNumber);
    // int* cellAmountLoaded = (int*) calloc(HASH_TABLE_CAPACITY((&hashTable)), sizeof(int));
    // assert(cellAmountLoaded);

    // for(size_t i = 0; i < HASH_TABLE_CAPACITY((&hashTable)); i++){
    //     cellNumber[i] = i;

    //     hashTableCell_t* curCell = &(HASH_TABLE_CELLS((&hashTable))[i]);
    //     cellAmountLoaded[i] =  HASH_TABLE_CELL_VALUE(curCell).size;
    // }

    // buildDiagram(cellNumber, cellAmountLoaded, HASH_TABLE_CAPACITY((&hashTable)), "images/diagrams/test.png");

    // free(cellNumber);
    // free(cellAmountLoaded);

    int cellNum = 0;
    for(size_t i = 0; i < nSearches; i++){
        size_t index = rand() % HASH_TABLE_CAPACITY((&hashTable));
        hashTableFind(&hashTable, words->ptrs[index].ptr, &cellNum);
    }

    hashTableDtor(&hashTable);
}