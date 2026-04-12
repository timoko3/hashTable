#include "handler.h"
#include "DSL.h"

#include "general/file.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

const char* PYTHON_FILE_NAME = "diagram.py";

void buildHashTableDiagram(hashTable_t* hashTable, const char* fileName){
    assert(hashTable);
    assert(fileName);

    fileDescription diagramFileDesc = {
        PYTHON_FILE_NAME,
        "wb"
    };

    FILE* pyDiagramFile = myOpenFile(&diagramFileDesc);
    assert(pyDiagramFile);

    fprintf(pyDiagramFile, "import matplotlib.pyplot as plt\n");
    fprintf(pyDiagramFile, "import numpy as np\n");

    fprintf(pyDiagramFile, "cellNum = [");
    for(size_t i = 0; i < HASH_TABLE_SIZE(hashTable); i++){
        fprintf(pyDiagramFile, "'%d'", i);
        if(i != (HASH_TABLE_SIZE(hashTable) - 1)) fprintf(pyDiagramFile, ",");
    }
    fprintf(pyDiagramFile, "]\n");

    fprintf(pyDiagramFile, "plt.figure(figsize=(12, 6))\n");    

    fprintf(pyDiagramFile, "values = [");    
    for(size_t i = 0; i < HASH_TABLE_SIZE(hashTable); i++){
        hashTableCell_t* curCell = &(HASH_TABLE_CELLS(hashTable)[i]);
        fprintf(pyDiagramFile, "%d", HASH_TABLE_CELL_VALUE(curCell).size);

        if(i != (HASH_TABLE_SIZE(hashTable) - 1)) fprintf(pyDiagramFile, ", ");
    }
    fprintf(pyDiagramFile, "]\n");

    fprintf(pyDiagramFile, "plt.xticks(range(0, len(cellNum), 10))\n");

    fprintf(pyDiagramFile, "plt.grid(axis='y', linestyle='--', alpha=0.5)\n");

    fprintf(pyDiagramFile, "plt.bar(cellNum, values)\n");

    fprintf(pyDiagramFile, "plt.title(\"Загрузка хэш-таблицы\")\n");


    fprintf(pyDiagramFile, "stats = (\n");
    fprintf(pyDiagramFile, "f\"Всего ячеек: {len(values)}\\n\"\n");
    fprintf(pyDiagramFile, "f\"Лоад-фактор: %.2f\\n\"\n", 
        (float) HASH_TABLE_AMOUNT_ELEMENTS(hashTable) / (float) HASH_TABLE_SIZE(hashTable));
    fprintf(pyDiagramFile, "f\"Пустые: {values.count(0)}\"\n");
    fprintf(pyDiagramFile, ")\n");


    fprintf(pyDiagramFile, "plt.text(0.8, 0.8, stats, transform=plt.gca().transAxes, bbox=dict(boxstyle=\"round\"))\n");

    
    fprintf(pyDiagramFile, "plt.savefig('%s')\n", fileName);

    fclose(pyDiagramFile);

    char buildDiagCommand[30] = "";
    sprintf(buildDiagCommand, "python3 %s", PYTHON_FILE_NAME);
    system(buildDiagCommand);
}