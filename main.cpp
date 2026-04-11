#include "hashtable.h"

#include "general/debug.h"
#include "general/file.h"

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

    for(size_t curWord = 0; curWord < words.count; curWord++){
        lprintf("wordLen = %llu\n", words.ptrs[curWord].len);
        lprintf("word: ");
        for(size_t curSymInd = 0; curSymInd < words.ptrs[curWord].len; curSymInd++){
            lprintf("%c", (words.ptrs[curWord].ptr)[curSymInd]);
        }
        lprintf("\n");
    }

    // hashTable_t hashTable;
    // hashTableCtor(&hashTable);

    // char testStr[10] = "hello\n";

    // hashTableInsert(&hashTable, testStr);

    // int cellNum = 0;
    // hashTableFind(&hashTable, testStr, &cellNum);

    // lprintf("foundCellNum = %d\n", cellNum);

    // hashTableDtor(&hashTable);

    return 0;
}