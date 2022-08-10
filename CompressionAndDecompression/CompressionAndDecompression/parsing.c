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


int checkIfFileExists(char* path) {
	FILE* fp;
	if (openFile(path, &fp, "r")) {
		closeFile(fp);
		return 1;
	}	
	return 0;

}

char* checkAndChangeOutputPath(char* outputFile, char* ex) {
	
	if (checkIfFileExists(outputFile)) {
		char* changedPath = (char*)malloc(strlen(outputFile) + 5);
		strncpy(changedPath, outputFile, strlen(outputFile) - EX_LEN);
		changedPath[strlen(outputFile) - EX_LEN] = '\0';
		strcat(changedPath, "-copy");
		strcat(changedPath, ex);
		return changedPath;
	}
	else
		return outputFile;
}


char* subString(char* fileName)
{
	//Parameter: file name - path to the file
	//The function cut the file path to name and extension.
	// save the eextension,
	//And return the name.
	char chr, * nameWithoutExtension = (char*)malloc(sizeof(char) * strlen(fileName)- EX_LEN),
		* extension = (char*)malloc(sizeof(char) * EX_LEN),
		* tmp = (char*)malloc(sizeof(char) * strlen(fileName));
	int cnt = 0;
	strcpy(tmp, fileName);
	while (tmp &&(*tmp != '.')) {
		cnt++;
		tmp++;
	}
	tmp++;
	strcpy(extension, tmp);
	details->inputExtension = extension;
	strncpy(nameWithoutExtension, fileName, cnt);
	nameWithoutExtension[cnt] = '\0';
	return nameWithoutExtension;
}

int parsing(char* sourceFilePath, char* mode)
{
	//params: source file path and mode,
	//the func parses the params and
	//according them perform compression or decompression
	int stat=0;
	FILE* outputFile;
	//open source file
	FILE* sourceFile;
	if (!openFile(sourceFilePath, &sourceFile, "r"))
		return 0;
	//save source file path
	details->inputFilePath = sourceFilePath;
	details->inputFileSize = findSize(sourceFile);
	if (details->inputFileSize > 100 * 1024 * 1024) {
		printf("Error: This file size is too large.\n The maximum supprted file size is 100MB\n");
		ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "The size of the source file is %ld bytes, too large than supported.\n", details->inputFileSize);
		return 0;
	}
	ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "The size of the source file is %ld bytes \n", details->inputFileSize);
	char* outputFileName = subString(sourceFilePath);
	//check the mode of operation
	if (!strcmp(mode, "compression"))
	{
		//check the extension 
		if (strcmp(details->inputExtension, "txt")) {
			ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "the extension doesn't match to compression\n");
			return 0;
		}
		//add extension '.lzw' to output file path
		strcat(outputFileName, ".lzw");
		//create and open output file
		if (!openFile(outputFileName, &outputFile, "ab+"))
			return 0;
		//save the output file path
		details->outputFilePath = outputFileName;
		//call compression function
		stat=compression(sourceFile, outputFile);
	}
	else if (!strcmp(mode, "decompression"))
	{
		//check the extension 
		if (strcmp(details->inputExtension, "lzw")) {
			ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "the extension doesn't match to decompression\n");
			return 0;
		}
		//add extension '.txt' to output file path
		strcat(outputFileName, ".txt");
		//The extension from the global table.
		if (!openFile(outputFileName, &outputFile, "a+"))
			return 0;
		//save the output file path
		details->outputFilePath = outputFileName;
		//call decompression function
		stat=decompression(sourceFile, outputFile);
	}
	return stat;
}