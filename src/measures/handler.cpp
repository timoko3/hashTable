#include "handler.h"
#include "DSL.h"

#include "general/file.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <malloc.h>
#undef log 
#include <math.h>

const char* PYTHON_FILE_NAME = "diagram.py";

void buildDiagram(int* x, int* y, int nValues, const char* fileName){
    assert(x);
    assert(y);
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
    for(size_t i = 0; i < nValues; i++){
        fprintf(pyDiagramFile, "'%d'", x[i]);
        if(i != (nValues - 1)) fprintf(pyDiagramFile, ",");
    }
    fprintf(pyDiagramFile, "]\n");

    fprintf(pyDiagramFile, "plt.figure(figsize=(12, 6))\n");    

    fprintf(pyDiagramFile, "values = [");    
    for(size_t i = 0; i < nValues; i++){
        fprintf(pyDiagramFile, "%d", y[i]);

        if(i != (nValues - 1)) fprintf(pyDiagramFile, ", ");
    }
    fprintf(pyDiagramFile, "]\n");

    fprintf(pyDiagramFile, "plt.xticks(range(0, len(cellNum), 250))\n");

    fprintf(pyDiagramFile, "plt.grid(axis='y', linestyle='--', alpha=0.5)\n");

    fprintf(pyDiagramFile, "plt.xlabel('Номер ячейки')\n");
    fprintf(pyDiagramFile, "plt.ylabel('Количество элементов')\n");

    fprintf(pyDiagramFile, "plt.title(\"Загрузка хэш-таблицы\")\n");

    float mean = countMean(y, nValues);
    float std  = countStd(y, nValues, mean);
    float cv   = std / mean;

    // показываем цветами выход из нормы
    fprintf(pyDiagramFile, "mean = %.2f\n", mean);
    fprintf(pyDiagramFile, "std = %.2f\n",  std);

    fprintf(pyDiagramFile, "colors = []\n");
    fprintf(pyDiagramFile, "for v in values:\n",             std);
    fprintf(pyDiagramFile, "\tif v > mean + std:\n",         std);
    fprintf(pyDiagramFile, "\t\tcolors.append('red')\n",     std);
    fprintf(pyDiagramFile, "\telif v > mean:\n",             std);
    fprintf(pyDiagramFile, "\t\tcolors.append('orange')\n",  std);
    fprintf(pyDiagramFile, "\telse:\n",  std);
    fprintf(pyDiagramFile, "\t\tcolors.append('green')\n",   std);
    
    fprintf(pyDiagramFile, "plt.bar(cellNum, values, color = colors, alpha=0.8)\n");

    fprintf(pyDiagramFile, "stats = (\n");
    fprintf(pyDiagramFile, "f\"Среднее: %.2f\\n\"\n", mean);
    fprintf(pyDiagramFile, "f\"Стандартное отклонение:  %.2f\\n\"\n", std );
    fprintf(pyDiagramFile, "f\"Коэф. вариации:   %.2f\\n\"\n", cv  );
    fprintf(pyDiagramFile, "f\"пустые ячейки: {values.count(0)}\"\n");
    fprintf(pyDiagramFile, ")\n");

    fprintf(pyDiagramFile, "plt.plot([], [], ' ', label=stats)\n");

    fprintf(pyDiagramFile, "plt.legend(loc='best')\n");

    // создаем линию mean
    fprintf(pyDiagramFile, "plt.axhline(y = %.2f, linewidth = 2.5, linestyle = '--', label=f'Среднее: %.2f')\n", mean, mean);
    
    // создаем линии std
    fprintf(pyDiagramFile, "plt.axhline(y = %.2f, linewidth = 2, linestyle = ':', label=f'+1σ')\n", mean + std);
    if(mean - std > 0){
        fprintf(pyDiagramFile, "plt.axhline(y = %.2f, linestyle = ':', label=f'-1σ')\n", mean - std);
    }

    // fprintf(pyDiagramFile, "plt.yscale('log')\n");
    fprintf(pyDiagramFile, "plt.legend()\n");

    fprintf(pyDiagramFile, "plt.tight_layout()\n");
    
    fprintf(pyDiagramFile, "plt.savefig('%s')\n", fileName);

    fclose(pyDiagramFile);

    char buildDiagCommand[30] = "";
    snprintf(buildDiagCommand, sizeof(buildDiagCommand), "python3 %s", PYTHON_FILE_NAME);
    system(buildDiagCommand);
}

float countMean(int* value, int nValues){
    assert(value);

    float mean = 0.0;

    for(size_t i = 0; i < nValues; i++){
        mean += value[i];
    }

    mean /= nValues;

    return mean;
}

float countStd(int* value, int nValues, float mean){
    assert(value);

    float std = 0.0;

    for(size_t i = 0; i < (size_t) nValues; i++){
        std += (value[i] - mean) * (value[i] - mean); 
    }

    std /= nValues;

    std = sqrt(std);

    return std;
}