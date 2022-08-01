#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "detailsStruct.h"
extern struct Details* details;
//init a dynamic array with 256 single charater strings
char** initArrray(int* status) {
	char chr[] = "  ";
	char c;

	//Allocates an array of size 256
	char** stringTable = (char**)malloc(sizeof(char*) * 256);
	if (stringTable == NULL) {
		fprintf(details->fpLogFile, "Unable to allocate the array for decompression.");
		*status = 0;
	}
	else 
		for (int i = 0; i < 256; i++)
		{
			c = i;
			*chr = c;
			*(chr + 1) = '\0';
			stringTable[i] = (char*)malloc(sizeof(char));
			if (stringTable[i])
				strcpy(stringTable[i], chr);
			else {
				fprintf(details->fpLogFile, "Unable to allocate array of chars.");
				*status = 0;
			}
		}	
	return stringTable;
}

int addarray(char** stringTable, int* lastCodeInTable, char firstChar, int prevCode) {
	char* insertString = malloc(sizeof(char));
	strcpy(insertString, stringTable[prevCode]);
	strncat(insertString, &firstChar, 1);
	stringTable = (char**)realloc(stringTable, sizeof(char*) * (*lastCodeInTable + 2));
	if (stringTable != NULL) {
		stringTable[++(*lastCodeInTable)] = malloc(sizeof(char));
		strcpy(stringTable[*lastCodeInTable], insertString);
		free(insertString);
		return 1;
	}
	fprintf(details->fpLogFile, "Unable to allocate array of chars.\n");
	free(insertString);
	return 0;
}
