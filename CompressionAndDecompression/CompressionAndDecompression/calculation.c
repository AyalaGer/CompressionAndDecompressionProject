#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "detailsStruct.h"

extern struct Details* details;

double compressionRatio()
{
	return details->outputFileSize / details->inputFileSize;
}

long runningTime()
{
	time_t current_time;
	time(&current_time);
	return current_time - details->startTime;

}
void calculation(char* mode)
{
	fprintf(details->fpLogFile, "calculation process has begun at: %s.",calcTime());
	if (!strcmp(mode, "compression")) {
		double ratio = compressionRatio();
		printf("%f", ratio);
		long time = runningTime();
		printf("%ld", time);
	}
	else if (!strcmp(mode, "decompression")) {
		long time = runningTime();
		printf("%ld", time);
	}
	else {
		printf("%s","ERROR!");
	}
	fprintf(details->fpLogFile, "calculation process complited successfully at: %s.", calcTime());
}