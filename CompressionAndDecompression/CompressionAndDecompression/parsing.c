#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compress.h"
#include "decompress.h"
#include "detailsStruct.h"
#include "filesHandling.h"
#define EX_LEN 4

extern struct Details* details;

char* subString(char* fileName)
{
	printf("%s", fileName);
	//Parameter: file name - path to the file
	//The function cut the file path to name and extension.
	//And return the name.
	char chr, * nameWithoutExtension = (char*)malloc(sizeof(char) * strlen(fileName)- EX_LEN),
		* extension = (char*)malloc(sizeof(char) * EX_LEN),
		* tmp = (char*)malloc(sizeof(char) * strlen(fileName));
	int cnt = 0;
	printf("%d", sizeof(char) * strlen(fileName) - EX_LEN + 1);
	strcpy(tmp, fileName);
	printf("%s", tmp);
	while (tmp &&(*tmp != '.')) {
		cnt++;
		tmp++;
	}
	tmp++;
	strcpy(extension, tmp);
	strncpy(nameWithoutExtension, fileName, cnt);
	nameWithoutExtension[cnt] = '\0';
	printf("%s", nameWithoutExtension);
	printf("%s\n", extension);
	printf("%s",nameWithoutExtension);
	return nameWithoutExtension;
}

int parsing(char* sourceFilePath, char* mode)
{
	printf("%s\n", sourceFilePath);
	//params: source file path and mode,
	//the func parses the params and
	//according them perform compression or decompression
	int stat=0;
	FILE* outputFile;
	FILE* sourceFile = fopen(sourceFilePath, "r");
	if (sourceFile == NULL) {
		fprintf(details->fpLogFile, "unable to open the source file: %s.\n", sourceFilePath);
		return 0;
	}
	details->inputFilePath = sourceFilePath;
	fprintf(details->fpLogFile, "Opening the source file: %s .\n", sourceFilePath);
	details->inputFileSize = findSize(sourceFile);
	fprintf(details->fpLogFile, "Size of the source file is %ld bytes \n", details->inputFileSize);
	char* outputFileName = subString(sourceFilePath);
	if (!strcmp(mode, "compression"))
	{
		strcat(outputFileName, ".lzw");
		outputFile = fopen(outputFileName, "ab+");
		if (outputFile == NULL) {
			fprintf(details->fpLogFile, "Failed while opening the output file: %s.\n", outputFileName);
		}
		fprintf(details->fpLogFile, "Opening the output file: %s.\n", outputFileName);
		details->outputFilePath = outputFileName;
		stat=compression(sourceFile, outputFile);
	}
	else if (!strcmp(mode, "decompression"))
	{
		strcat(outputFileName, ".txt");
		//The extension from the global table.
		outputFile = fopen(outputFileName, "a+");
		if (outputFile == NULL) {
			fprintf(details->fpLogFile, "Failed while opening the output file: %s.\n", outputFileName);
		}
		fprintf(details->fpLogFile, "Opening the output file: %s.\n", outputFileName);
		details->outputFilePath = outputFileName;
		stat=decompression(sourceFile, outputFile);
	}
	return stat;
}