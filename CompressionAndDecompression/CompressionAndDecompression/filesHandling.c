#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "detailsStruct.h"
#include "log.h"
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
		LOG_INFO(__func__,"Unable to open the file")
		return 0;
	}
	LOG_INFO(__func__,"File opened successfully")
	return 1;
}

int removeFile(char* fPath) {
	if (remove(fPath) == 0) {
		LOG_INFO(__func__,"Deleted file successfuly")
		return 1;
	}
	else
	{
		LOG_INFO(__func__,"The file cannot be deleted")
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
