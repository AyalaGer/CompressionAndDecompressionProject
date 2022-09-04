#pragma once
#ifndef SEQUENCE_H
#define SEQUENCE_H
#include <stdbool.h>

typedef struct _sequence {
    int count;
    unsigned char* data;
} Sequence;

Sequence* newSequence(unsigned char firstByte);
void deleteSequence(Sequence* sequence);
Sequence* copySequenceAppend(Sequence* sequence, unsigned char addByte);
void outputSequence(Sequence* sequence,
int (*writeFunc)(unsigned char c, void* context), void* context);
bool identicalSequences(Sequence* a, Sequence* b);

#endif