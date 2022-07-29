#define _CRT_SECURE_NO_WARNINGS
#define TABLE_SIZE 4094
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "test.h"
#include "detailsStruct.h"
#include "binaryFile.h"
#include "array.h"
extern struct Details details;

int decompression(FILE* fpIn, FILE* fpOut) {
	fprintf(details.fpLogFile, "Decompression process start at: %ld.", time(NULL));
	//prevCode- contains the previous code in the file.
	//nextCode- read the file code by code.
	//outputStr- translation of the codes, the output to the decompressed file.
	//firstChar- save the first character of the output string.
	char firstChar, * outputStr = malloc(sizeof(char));
	int prevCode, nextCode, lastCodeInTable = 255, status = 1;
	char** stringTable = initArrray(&status);
	if (!status)
		return 0;
	//read first code from the input file
	prevCode = readBinary(fpIn);
	if (prevCode == 0) {
		fprintf(details.fpLogFile, "empty decompress file");
	}
	//write to output file the translation of the first code-stringTable[prevCode] .
	fprintf(fpOut, "%s", stringTable[prevCode]);
	//while(there is still data to read) , nextcode=read code
	while (nextCode = readBinary(fpIn) > 0) {
		if (nextCode > lastCodeInTable) {
			strcpy(outputStr, stringTable[prevCode]);
			strncat(outputStr, &firstChar, 1);
		}
		else
			strcpy(outputStr, stringTable[nextCode]);// outputStr=stringTable[nextCode]  אולי מספיק לעשות הצבעה   
		fprintf(fpOut, "%s", outputStr);
		firstChar = *outputStr;
		if (lastCodeInTable < TABLE_SIZE) {
			if (!addarray(stringTable, &lastCodeInTable))
				return 0;
		}
		prevCode = nextCode;
	}
	free(stringTable);
	fprintf(details.fpLogFile, "Decompression process complited successfully at: %ld.", time(NULL));
	if (closeFile(fpIn) && closeFile(fpOut))
		return 1;
	return 0;

}