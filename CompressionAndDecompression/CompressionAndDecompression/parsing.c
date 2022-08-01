#define _CRT_SECURE_NO_WARNINGS
#include "compress.h"
#include "decompress.h"
#include "detailsStruct.h"
extern struct Details* details;
long int findSize(FILE* fp)
{
	fseek(fp, 0L, SEEK_END);

	// calculating the size of the file
	long int size = ftell(fp);

	// closing the file
	fclose(fp);

	return size;
}
char* subString(char* fileName)
{
	//Parameter: file name - path to the file
	//The function cut the file path to name and extension.
	//And return the name.
	char* dotPtr = strrchr(fileName, '.');
	char* nameWithoutExtension = NULL, * extension = NULL;
	*dotPtr = '\0';
	strcpy(nameWithoutExtension, fileName);
	*dotPtr = '.';
	strcpy(extension, ++dotPtr);
	details->inputExtension = extension;
	return nameWithoutExtension;
}

char* parsing(char* sourceFilePath, char* mode)
{
	//params: source file path and mode,
	//the func parses the params and
	//according them perform compression or decompression
	FILE* outputFile;
	FILE* sourceFile = fopen(sourceFilePath, "r");
	if (sourceFile == NULL) {
		fprintf(details->fpLogFile, "Can't opening the source file.\n");

	}
	details->inputFilePath = sourceFilePath;
	fprintf(details->fpLogFile, "Opening the source file: %s .\n", sourceFilePath);
	details->inputFileSize = findSize(sourceFile);
	fprintf(details->fpLogFile, "Size of the source file is %ld bytes \n", details->inputFileSize);
	char* outputFileName = subString(sourceFilePath);
	if (strcmp(mode, "compression"))
	{
		strcat(outputFileName, ".lzw");
		outputFile = fopen(outputFileName, "+a");
		if (outputFile == NULL) {
			fprintf(details->fpLogFile, "Can't opening the output file.\n");
		}
		fprintf(details->fpLogFile, "Opening the output file: %s.\n", outputFileName);
		compression(sourceFile, outputFile);
	}
	else if (strcmp(mode, "decompression"))
	{
		strcat(outputFileName, ".txt");
		//The extension from the global table.
		outputFile = fopen(outputFileName, "+a");
		if (outputFile == NULL) {
			fprintf(details->fpLogFile, "Can't opening the output file.\n");
		}
		fprintf(details->fpLogFile, "Opening the output file: %s.\n", outputFileName);
		decompression(sourceFile, outputFile);
	}

	return outputFileName;
}