#ifndef HANDLER_H
#define HANDLER_H

#include "hashTable.h"

void buildDiagram(int* x, int* y, int nValues, const char* fileName);

float countMean(int* value, int nValues);
float countStd(int* value, int nValues, float mean);

#endif /* HANDLER_H */