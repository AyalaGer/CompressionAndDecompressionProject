#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "parsing.h"
#include "detailsStruct.h"
#include "calculation.h"

extern struct Details* details;
void lzwCompressionDecompression(char* filePath, char* mode) {
	//params: the user arguments- file path and mode 
	//the function  is shell func which execute the program.
	//save the time and print it to logging file
	time_t seconds;
	time(&seconds);
	struct tm* tm = localtime(&seconds);
	//save the start time. 
	details->startTime = seconds;
	//open a log file.
	FILE* fpLogFile = fopen("logfile.txt", "a+");
	if (fpLogFile == NULL) {
		return;
	}
	//save pointer to log file.
	details->fpLogFile = fpLogFile;
	ENABLE_DEBUG_LOG&& fprintf(fpLogFile, "[%s] Log started\n", calcTime());
	//pass the arguments to parsing
	//the function call compression or decompression 
	if (parsing(filePath, mode)) {
		printf("The file is: %s\n", details->outputFilePath);
		//calculate the compression ratio and the running time
		calculation(mode);
	}

	fclose(details->fpLogFile);
}