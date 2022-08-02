#pragma once
#include <stdio.h>
char* calcTime();
int fileSize(FILE* fp);
int wrapDecompression(FILE* fpCompressed);
int areFileSizesEquals(int sourceFileSize, int decompressedFileSize);
int chComparison(FILE* fpSource);
int kComparison(FILE* fpSource, FILE* fpDecompressed);
int mComparison(FILE* fpSource, FILE* fpDecompressed);
int goToTheRelevantComparison(int sizeFile, FILE* fpSouce, FILE* fpDeconpressed);
int wrapCompare(FILE* fpSource, FILE* fpCompressed);






