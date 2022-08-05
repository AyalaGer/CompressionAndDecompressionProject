#pragma once
#include <stdio.h>
struct Details {
	char* inputFilePath;
	char* outputFilePath;
	char* inputExtension;
	int outputFileSize;
	int inputFileSize;
	int startTime;
	FILE* fpLogFile;
};
struct Details* details;
struct Details* allocateDetails();
char* calcTime();

