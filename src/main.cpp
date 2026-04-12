#include "hashtable.h"

#include "general/debug.h"
#include "general/file.h"

#include "measures/handler.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>

const size_t MAX_FILE_NAME_LENGTH = 64;

int main(int argc, char* argv[]){
    char wordsFileName[MAX_FILE_NAME_LENGTH] = "";
    if(argc == 3){
        if(!strcmp("-f", argv[1])){
            strcpy(wordsFileName, argv[2]);
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
    
    lprintf("buffer = %s, bufferSize = %llu", wordsBuffer, wordsFileSize);

    words_t words = divideBufferToWords(wordsBuffer, wordsFileSize);

    // dumpWords(&words);

    hashTable_t hashTable;
    hashTableCtor(&hashTable);

    // char testStr[10] = "hello\n";

    for(size_t curWord = 0; curWord < words.count; curWord++){
        hashTableInsert(&hashTable, words.ptrs[curWord].ptr);
    }

    // for(size_t i = 0; i < hashTable.size; i++){
    //     listGraphDump(&hashTable.cells[i].value);
    // }

    buildHashTableDiagram(&hashTable, "exDiag.png");


    // hashTableFind(&hashTable, testStr, &cellNum);


    hashTableDtor(&hashTable);

    return 0;
}