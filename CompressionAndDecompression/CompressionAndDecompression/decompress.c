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
	time_t t = time(NULL);
	struct tm* tm = localtime(&t);
	fprintf(details.fpLogFile, "Decompression process start at: %s.\n", asctime(tm));
	//prevCode- contains the previous code in the file.
	//nextCode- read the file code by code.
	//outputStr- translation of the codes, the output to the decompressed file.
	//firstChar- save the first character of the output string.
	char firstChar, * outputStr = malloc(sizeof(char)), * insertString = malloc(sizeof(char));
	int prevCode, nextCode, lastCodeInTable = 255, status = 1;
	//Init the array
	char** stringTable = initArrray(&status);
	if (!status)//if unable to init the array.
		return 0;
	//read first code from the input file
	prevCode = readBinary(fpIn);
	if (prevCode == 0) 
		fprintf(details.fpLogFile, "empty decompress file: %s\n",details.outputFilePath);
	//write to output file the translation of the first code-stringTable[prevCode] .
	fprintf(fpOut, "%s", stringTable[prevCode]);
	//while(there is still data to read) , nextcode=read code
	while (nextCode = readBinary(fpIn) > 0) {
		//if the code doesn't yet exist in the array.
		if (nextCode > lastCodeInTable) {
			//outputStr=translation of prevCode
			strcpy(outputStr, stringTable[prevCode]);
			//outputStr=outputStr+firstChar
			strncat(outputStr, &firstChar, 1);
		}
		else
			strcpy(outputStr, stringTable[nextCode]);// outputStr=stringTable[nextCode] 
		//write the str to the output file
		fprintf(fpOut, "%s", outputStr);
		//firstChar=first char of outputStr
		firstChar = *outputStr;
		//if the table isn't too big
		if (lastCodeInTable < TABLE_SIZE) {
			strcpy(insertString, stringTable[prevCode]);
			strncat(insertString, &firstChar, 1);
			stringTable = (char**)realloc(stringTable, sizeof(char*) * (lastCodeInTable + 2));
			stringTable[++lastCodeInTable] = malloc(sizeof(char));
			strcpy(stringTable[lastCodeInTable], insertString);
			/*if (!addarray(stringTable, &lastCodeInTable))
				return 0;*/
		}	
		//prevCode save the current code
		prevCode = nextCode;
	}
	//free the dynamic array and the other allocations
	free(stringTable);
	free(insertString);
	free(outputStr);
	t = time(NULL);
	tm= localtime(&t);
	fprintf(details.fpLogFile, "Decompression process complited successfully at: %s.\n", asctime(tm));
	if (closeFile(fpIn) ) {
		fprintf(details.fpLogFile, "The compressed file closed successfully\n");
		if (closeFile(fpOut)) {
			fprintf(details.fpLogFile, "The decompressed file closed successfully\n");
			return 1;
		}
		return 0
	}
	return 0;
}