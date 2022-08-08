#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "detailsStruct.h"

extern struct Details* details;

int closeFile(FILE* fp) {
	if (fclose(fp) == 0)
		return 1;
	else
		return 0;

}

int openFile(char* fPath, FILE** fp, char* mode) {
	*fp = fopen(fPath, mode);
	if (*fp == NULL) {
		fprintf(details->fpLogFile, "Unable to open the file for %s", mode);
		return 0;
	}
	fprintf(details->fpLogFile, "File opened for %s successfully", mode);
	return 1;
}

int removeFile(char* fPath) {
	if (remove(fPath) == 0) {
		fprintf(details->fpLogFile, "deleted file successfuly");
		return 1;
	}
	else
	{
		fprintf(details->fpLogFile, "deleted file does not success");
		return 0;
	}
}


//function to calculate the file size to verify which effective 'over on the file' to perform -
//(over character character or over kilobyte kilobyte or megabyte megabyte).
long int findSize(FILE* fp)
{
	// seek to end of file.
	fseek(fp, 0, SEEK_END);
	// get current file pointer.
	int	size = ftell(fp);
	// seek back to beginning of file.
	fseek(fp, 0, SEEK_SET);
	return size;
}
