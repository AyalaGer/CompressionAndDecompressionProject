#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compress.h"
#include "decompress.h"
#include "detailsStruct.h"
#include "filesHandling.h"
#include "log.h"
extern struct Details* details;

//param: file name
//the function check is file with the same name exists
int checkIfFileExists(char* path) {
	FILE* fp;
	if (openFile(path, &fp, "r")) {
		closeFile(fp);
		return SUCCESS;
	}	
	return FAILURE;

}

//the function checks if file with the same name like 'outputFile' exists, 
//so change the name by concat the word 'copy'
char* checkAndChangeOutputPath(char* outputFile, char* ex) {
	//length of file name + length of '-copy'
	int sizePath = strlen(outputFile) + 5;
	//length of file name without the extension
	int lenNamePath = strlen(outputFile) - 4;
	char* changedPath=(char*)malloc(strlen(outputFile));
	if (!changedPath) {
		LOG_INFO(__func__, "unable to allocate memory")
		exit(1);
	}

	strcpy(changedPath, outputFile);
	//while file with the same name is exist
	while (checkIfFileExists(changedPath)) {
		//allocate a memory
		changedPath = (char*)malloc(sizePath);
		if (!changedPath) {
			LOG_INFO(__func__, "unable to allocate memory")
			exit(1);
		}
		//add '-copy' to the name
		strncpy(changedPath, outputFile, lenNamePath);
		changedPath[lenNamePath] = '\0';
		strcat(changedPath, "-copy");
		strcat(changedPath, ex);

		//update the length of path
		sizePath= strlen(changedPath) + 5;
		lenNamePath= strlen(changedPath) - 4;
	}
		return changedPath;
}

//Parameter: file name - path to the file
//The function cut the file path into two: name and extension.
// save the extension,
//And return the name.
char* splitToNameAndExtension(char* fileName )
{
	int lenExtension = 4;
	int lenOfNamePath = strlen(fileName);
	char chr, * nameWithoutExtension = (char*)malloc(sizeof(char) * lenOfNamePath),
		* tmp = (char*)malloc(sizeof(char) * strlen(fileName)+1);
	if (!nameWithoutExtension|| !tmp) {
		LOG_INFO(__func__, "unable to allocate memory")
			exit(1);
	}
	int cnt = 0;
	strcpy(tmp, fileName);
	

	//find the location of the dot
	tmp = strchr(tmp, '.');
	tmp++;
	details->inputExtension = (char*)malloc(sizeof(char) * lenExtension);
	if (!details->inputExtension) {
		LOG_INFO(__func__, "unable to allocate memory")
			exit(1);
	}
	//save the extension in the global struct
	strcpy(details->inputExtension, tmp);
	//cut the name without extension
	strncpy(nameWithoutExtension, fileName, lenOfNamePath - lenExtension);
	nameWithoutExtension[lenOfNamePath - lenExtension] = '\0';
	//free(tmp);
	return nameWithoutExtension;
}


//params: source file path and mode,
//the func parses the params and
//according them perform compression or decompression
int parsing(char* sourceFilePath, char* mode)
{
	int status=FAILURE;
	int maxFileSize = 100 * 1024 * 1024;
	FILE* outputFile;
	FILE* sourceFile;

	//open source file
	status = openFile(sourceFilePath, &sourceFile, "rb");
	if (status == FAILURE)
		return status;

	//save source file path
	details->inputFilePath = sourceFilePath;

	//calculate the source file size
	details->inputFileSize = findSize(sourceFile);
	if (details->inputFileSize > maxFileSize) {
		printf("Error: This file size is too large.\n The maximum supprted file size is 100MB\n");
		LOG_INFO(__func__,"The size of the source file is too large than supported.")
		return FAILURE;
	}

	LOG_INFO(__func__, "The size of the source file is valid")
	char* outputFileName = splitToNameAndExtension(sourceFilePath);
	//check the mode of operation
	if (!strcmp(mode, "compression"))
	{
		//check the extension 
		if (strcmp(details->inputExtension, "txt")) {
			LOG_INFO(__func__,"the extension doesn't match to compression")
			return FAILURE;
		}
		//add extension '.lzw' to output file path
		strcat(outputFileName, ".lzw");
		//check if path exist and rename and save the name
		details->outputFilePath = checkAndChangeOutputPath(outputFileName, ".lzw");
		//create and open output file
		if (openFile(details->outputFilePath, &outputFile, "ab+")== FAILURE)
			return FAILURE;
		//call compression function
		status=compression(sourceFile, outputFile);
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
		if (openFile(details->outputFilePath, &outputFile, "a+")== FAILURE)
			return FAILURE;

		//call decompression function
		status=decompression(sourceFile, outputFile);
	}
	return status;
}