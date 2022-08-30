#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "parsing.h"
#include "detailsStruct.h"
#include "calculation.h"
#include "log.h"
extern struct Details* details;
void lzwCompressionDecompression(char* filePath, char* mode) {
	//params: the user arguments- file path and mode 
	//the function  is shell func which execute the program.
	//save the time and print it to logging file
	//save the start time. 
	details->startTime = clock();
	//open a log file.
	CREATE_LOG_FILE
	//pass the arguments to parsing
	//the function call compression or decompression 
	if (parsing(filePath, mode)) {
		printf("The file is: %s\n", details->outputFilePath);
		//calculate the compression ratio and the running time
		calculation(mode);
	}
	CLOSE_LOG
}