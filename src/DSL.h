#define HASH_TABLE_SIZE(hashTable)             hashTable->size
#define HASH_TABLE_AMOUNT_ELEMENTS(hashTable)  hashTable->amountElements
#define HASH_TABLE_FUNCTION(hashTable)         hashTable->hashFunction
#define HASH_TABLE_CELLS(hashTable)            hashTable->cells

#define HASH_TABLE_CELL_VALUE(hashTableCell)   hashTableCell->value
#define HASH_TABLE_CELL_HASH(hashTableCell)    hashTableCell->hash
