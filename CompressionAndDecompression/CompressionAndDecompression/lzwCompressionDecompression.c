#define _CRT_SECURE_NO_WARNINGS
#include "parsing.h"
#include "detailsStruct.h"
#include "calculation.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
extern struct Details details;
void lzwCompressionDecompression(char* filePath, char* mode) {
	//params: the user arguments- file path and mode 
	//the function  is shell func which execute the program.
	//save the time and print it to logging file
	time_t seconds;
	time(&seconds);
	details.startTime = seconds;
	//open a logging file
	FILE* fpLogFile = fopen("loggingfile.txt", "a+");
	if (fpLogFile == NULL) {
		//print error and exit
		exit(1);
	}
	fprintf(fpLogFile, "open logging file\n");
	details.fpLogFile = fpLogFile;
	fprintf(fpLogFile, "start exexcute at: %ld\n", seconds);
	char* outputFileName = parsing(filePath, mode);
	calculation();
}