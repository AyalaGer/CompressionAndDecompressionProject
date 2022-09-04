#pragma once
#include <stdio.h>
#include <time.h>
enum status { SUCCESS = 1, FAILURE = 0 };
struct Details {
	char* inputFilePath;
	char* outputFilePath;
	char* inputExtension;
	int outputFileSize;
	int inputFileSize;
	clock_t startTime;
	FILE* fpLogFile;
};
struct Details* details;
struct Details* allocateDetails();
char* calcTime();

