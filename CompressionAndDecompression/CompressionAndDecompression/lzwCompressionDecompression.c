#define _CRT_SECURE_NO_WARNINGS
#include "parsing.h"
#include "detailsStruct.h"
#include "calculation.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
extern struct Details* details;
void lzwCompressionDecompression(char* filePath, char* mode) {
	//params: the user arguments- file path and mode 
	//the function  is shell func which execute the program.
	//save the time and print it to logging file
	time_t seconds;
	time(&seconds);
	struct tm* tm = localtime(&seconds);
	details->startTime = seconds;
	//open a log file
	FILE* fpLogFile = fopen("logfile.txt", "a+");
	if (fpLogFile == NULL) {
		printf("error");
		exit(1);//check if good(?)
	}
	fprintf(fpLogFile, "open log file\n");
	details->fpLogFile = fpLogFile;
	fprintf(fpLogFile, "start exexcute at: %s\n", asctime(tm));
	//pass the arguments to parsing
	//the function call compression or decompression 
	char* outputFileName = parsing(filePath, mode);
	//calculate the compression ratio and the running time
	calculation(mode);
	fclose(details->fpLogFile);
}