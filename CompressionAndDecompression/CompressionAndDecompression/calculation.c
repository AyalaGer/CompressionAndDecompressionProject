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
	ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "[%s] Calculation started.\n",calcTime());
	if (!strcmp(mode, "compression")) {
		double ratio = compressionRatio();
		ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "The compression ratio is %f\n", ratio);
		printf("The compression ratio is %f\n", ratio);
		long time = runningTime();
		ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "The running time of %s is %ld\n", mode, time);
		printf("The running time of %s is %ld\n",mode,time);
	}
	else {
		long time = runningTime();
		ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "The running time of %s is %ld\n", mode, time);
		printf("The running time of %s is %ld", mode, time);
	}
	ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "[%s] Calculation process completed successfully.", calcTime());
}