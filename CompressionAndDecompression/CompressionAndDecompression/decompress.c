#define _CRT_SECURE_NO_WARNINGS
#define TABLE_SIZE 1<<16
#include <stdio.h>
#include <stdlib.h>
#include "sequence.h"
#include "filesHandling.h"
#include "detailsStruct.h"
#include "binaryFile.h"
#include "array.h"

extern struct Details* details;

void writeToTxtFile(FILE* fp, Sequence* str) {
	for (int i = 0; i < str->count; i++)
		putc((unsigned int)str->data[i], fp);
}

int decompression(FILE* fpIn, FILE* fpOut) {
	ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "[%s] Decompression started.\n", calcTime());
	//prevCode- contains the previous code in the file.
	//nextCode- read the file code by code.
	//outputStr- translation of the codes, the output to the decompressed file.
	//firstChar- save the first character of the output string.
	char firstChar;
	Sequence* outputStr, * insertString;
	int prevCode, nextCode, lastCodeInTable = 255, status = 1;
	Sequence* stringTable[TABLE_SIZE];	
	//Init the array
	initArray(stringTable);
	//read first code from the input file
	prevCode = read16bits(fpIn);
	if (prevCode == -1) {
		ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "The compressed file is empty\n");
		return 0;
	}		
	//write to output file the translation of the first code-stringTable[prevCode] .
	writeToTxtFile(fpOut, stringTable[prevCode]);
	firstChar = *(stringTable[prevCode]->data);
	//while(there is still data to read) , nextcode=read code
	while ((nextCode = read16bits(fpIn)) != -1) {
		//if the code doesn't yet exist in the array.
		if (nextCode > lastCodeInTable) {
			//outputStr=translation of prevCode
			outputStr = stringTable[prevCode];	
			//outputStr=outputStr+firstChar
			outputStr = copySequenceAppend(outputStr, firstChar);
		}
		else
			outputStr = stringTable[nextCode];
		//write the str to the output file
		writeToTxtFile(fpOut, outputStr);
		//firstChar=first char of outputStr
		firstChar = *(outputStr->data);
		//if the table isn't too big
		if (lastCodeInTable + 1 < TABLE_SIZE) {
			insertString = stringTable[prevCode];
			insertString = copySequenceAppend(insertString, firstChar);
			stringTable[++lastCodeInTable] = insertString;
		}	
		//prevCode save the current code
		prevCode = nextCode;
	}
	//free the array and the other allocations
	//deleteTable(stringTable);
	//deleteSequence(insertString);
	//deleteSequence(outputStr);
	
	ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "[%s] Decompression completed successfully.\n", calcTime());
	if (closeFile(fpIn) ) {
		ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "The compressed file closed successfully\n");
		if (closeFile(fpOut)) {
			ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "The decompressed file closed successfully\n");
			return 1;
		}
		return 0;
	}
	return 0;
}