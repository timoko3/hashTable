#include "handler.h"
#include "DSL.h"

#include "general/file.h"

#include <stdio.h>
#include <assert.h>

void buildHashTableDiagram(hashTable_t* hashTable, const char* fileName){
    assert(hashTable);
    assert(fileName);

    fileDescription diagramFileDesc = {
        "test.py",
        "wb"
    };

    FILE* pyDiagramFile = myOpenFile(&diagramFileDesc);
    assert(pyDiagramFile);

    fprintf(pyDiagramFile, "import matplotlib.pyplot as plt\n");

    fprintf(pyDiagramFile, "cellNum = [");
    for(size_t i = 0; i < HASH_TABLE_SIZE(hashTable); i++){
        fprintf(pyDiagramFile, "'%d'", i);
        if(i != (HASH_TABLE_SIZE(hashTable) - 1)) fprintf(pyDiagramFile, ",");
    }
    fprintf(pyDiagramFile, "]\n");

    fprintf(pyDiagramFile, "values = [");    
    for(size_t i = 0; i < HASH_TABLE_SIZE(hashTable); i++){
        hashTableCell_t* curCell = &(HASH_TABLE_CELLS(hashTable)[i]);
        fprintf(pyDiagramFile, "%d", HASH_TABLE_CELL_VALUE(curCell).size);

        if(i != (HASH_TABLE_SIZE(hashTable) - 1)) fprintf(pyDiagramFile, ", ");
    }
    fprintf(pyDiagramFile, "]\n");

    fprintf(pyDiagramFile, "plt.bar(cellNum, values)\n");

    fprintf(pyDiagramFile, "plt.title(\"Загрузка хэш-таблицы\")\n");
    
    fprintf(pyDiagramFile, "plt.savefig('%s')\n", fileName);

    fclose(pyDiagramFile);
}