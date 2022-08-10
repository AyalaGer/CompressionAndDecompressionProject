#define _CRT_SECURE_NO_WARNINGS
#define TABLE_SIZE 1<<16
#include <stdio.h>
#include <stdlib.h>
#include "detailsStruct.h"
#include "sequence.h"

extern struct Details* details;

//init an array with 256 single charater strings
void initArray(Sequence* stringTable[TABLE_SIZE]) {
	for (unsigned int i = 0; i < 256; i++)
	{
		Sequence* sequence = newSequence((unsigned char)i);
		stringTable[i] = sequence;
	}
}

int addarray(char** stringTable, int* lastCodeInTable, char firstChar, int prevCode) {
	char* insertString = (char*)malloc(sizeof(char));
	strcpy(insertString, stringTable[prevCode]);
	strncat(insertString, &firstChar, 1);
	stringTable = (char**)realloc(stringTable, sizeof(char*) * (*lastCodeInTable + 2));
	if (stringTable != NULL) {
		stringTable[++(*lastCodeInTable)] =(char*) malloc(sizeof(char));
		strcpy(stringTable[*lastCodeInTable], insertString);
		free(insertString);
		return 1;
	}
	fprintf(details->fpLogFile, "Unable to allocate array of chars.\n");
	free(insertString);
	return 0;
}
