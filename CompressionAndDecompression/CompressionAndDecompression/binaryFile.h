#pragma once
void write16bits(FILE* output, int code);
int read16bits(FILE* output);
void writeBinary(FILE* output, int code);
int readBinary(FILE* input);
void write16bitsToBuffer(char buffer[], int ind, int code);