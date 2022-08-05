#pragma once
#include <stdio.h>
int wrapDecompression(FILE* fpCompressed);
int areFileSizesEquals(int sourceFileSize, int decompressedFileSize);
//int chComparison(FILE* fpSource);
int kComparison(FILE* fpSource, unsigned char fpSourceKBuffer[], unsigned char fpDecompressedKBuffer[], int fileSize);
int goToTheRelevantComparison(int sizeFile, FILE* fpSouce, FILE* fpDeconpressed);
int wrapCompare();






