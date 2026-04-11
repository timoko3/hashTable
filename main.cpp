#include "hashtable.h"

#include "general/debug.h"
#include "general/file.h"

#include <stdio.h>
#include <string.h>

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
        "rb",
        wordsFileName
    };
    FILE*  wordsFilePtr     = myOpenFile(&wordsFileDesc);
    size_t wordsFileSize    = getFileSize(wordsFileName);
    
    char* wordsBuffer = getTextToBuffer(wordsFilePtr, wordsFileSize);
    


    hashTable_t hashTable;
    hashTableCtor(&hashTable);

    char testStr[10] = "hello\n";

    hashTableInsert(&hashTable, testStr);

    int cellNum = 0;
    hashTableFind(&hashTable, testStr, &cellNum);

    lprintf("foundCellNum = %d\n", cellNum);

    hashTableDtor(&hashTable);

    return 0;
}