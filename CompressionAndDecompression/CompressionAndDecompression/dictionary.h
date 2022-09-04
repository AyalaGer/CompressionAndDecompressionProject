#pragma once
#ifndef DICT_H
#define DICT_H
#include <stdbool.h>
#include "sequence.h"


typedef struct _entry {
    Sequence* key;
    int value;
    struct _entry* next;
} Entry;

typedef struct _dict {
    Entry** table;
    int size;
} Dict;
Dict* newDict(unsigned int hashSize);
void deleteDictDeep(Dict* dict);
bool searchDict(Dict* dict, Sequence* key, unsigned int* code);
void insertDict(Dict* dict, Sequence* key, unsigned int  code);

#endif