#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compress.h"
#include "decompress.h"
#include "detailsStruct.h"
#include "filesHandling.h"
#include "log.h"
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
	int sizePath = strlen(outputFile) + 5;
	int lenNamePath = strlen(outputFile) - 4;
	char* changedPath=(char*)malloc(strlen(outputFile));
	strcpy(changedPath, outputFile);
	while (checkIfFileExists(changedPath)) {
		changedPath = (char*)malloc(sizePath);
		strncpy(changedPath, outputFile, lenNamePath);
		changedPath[lenNamePath] = '\0';
		strcat(changedPath, "-copy");
		strcat(changedPath, ex);
		sizePath= strlen(changedPath) + 5;
		lenNamePath= strlen(changedPath) - 4;
	}
		return changedPath;
}


char* subString(char* fileName)
{
	//Parameter: file name - path to the file
	//The function cut the file path to name and extension.
	// save the eextension,
	//And return the name.
	int exLen = 4;
	int lenOfNamePath = strlen(fileName);
	char chr, * nameWithoutExtension = (char*)malloc(sizeof(char) * lenOfNamePath),
		* tmp = (char*)malloc(sizeof(char) * strlen(fileName));
	int cnt = 0;
	strcpy(tmp, fileName);
	tmp = strchr(tmp, '.');
	tmp++;
	details->inputExtension = (char*)malloc(sizeof(char) * exLen);
	strcpy(details->inputExtension, tmp);
	strncpy(nameWithoutExtension, fileName, lenOfNamePath - exLen);
	nameWithoutExtension[lenOfNamePath - exLen] = '\0';
	return nameWithoutExtension;
}

int parsing(char* sourceFilePath, char* mode)
{
	//params: source file path and mode,
	//the func parses the params and
	//according them perform compression or decompression
	int stat=0;
	int maxFileSize = 100 * 1024 * 1024;
	FILE* outputFile;
	//open source file
	FILE* sourceFile;
	if (!openFile(sourceFilePath, &sourceFile, "r"))
		return 0;
	//save source file path
	details->inputFilePath = sourceFilePath;
	details->inputFileSize = findSize(sourceFile);
	if (details->inputFileSize > maxFileSize) {
		printf("Error: This file size is too large.\n The maximum supprted file size is 100MB\n");
		LOG_INFO(__func__,"The size of the source file is too large than supported.")
		return 0;
	}
	LOG_INFO(__func__, "The size of the source file is valid")
	char* outputFileName = subString(sourceFilePath);
	//check the mode of operation
	if (!strcmp(mode, "compression"))
	{
		//check the extension 
		if (strcmp(details->inputExtension, "txt")) {
			LOG_INFO(__func__,"the extension doesn't match to compression")
			return 0;
		}
		//add extension '.lzw' to output file path
		strcat(outputFileName, ".lzw");
		//check if path exist and rename and save the name
		details->outputFilePath = checkAndChangeOutputPath(outputFileName, ".lzw");
		//create and open output file
		if (!openFile(details->outputFilePath, &outputFile, "ab+"))
			return 0;
		//call compression function
		stat=compression(sourceFile, outputFile);
	}
	else if (!strcmp(mode, "decompression"))
	{
		//check the extension 
		if (strcmp(details->inputExtension, "lzw")) {
			LOG_INFO(__func__,"the extension doesn't match to decompression")
			return 0;
		}
		//add extension '.txt' to output file path
		strcat(outputFileName, ".txt");
		//check if path exist and rename and save the name
		details->outputFilePath = checkAndChangeOutputPath(outputFileName, ".txt");
		if (!openFile(details->outputFilePath, &outputFile, "a+"))
			return 0;
		//call decompression function
		stat=decompression(sourceFile, outputFile);
	}
	return stat;
}