#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "detailsStruct.h"

extern struct Details* details;

double compressionRatio()
{
	return (double)details->outputFileSize / (double)details->inputFileSize;
}

double runningTime()
{
	clock_t curTime = clock();
	time_t current_time;
	time(&current_time);
	return  (double)(curTime - details->startTime) / CLOCKS_PER_SEC;;

}
void calculation(char* mode)
{
	ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "[%s] Calculation started.\n",calcTime());
	if (!strcmp(mode, "compression")) {
		double ratio = compressionRatio();
		ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "The compression ratio is %f\n", ratio);
		printf("The compression ratio is %f\n", ratio);
		double time = runningTime();
		ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "The running time of %s is %f\n", mode, time);
		printf("The running time of %s is %f\n",mode,time);
	}
	else {
		double time = runningTime();
		ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "The running time of %s is %f\n", mode, time);
		printf("The running time of %s is %f", mode, time);
	}
	ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "[%s] Calculation process completed successfully.", calcTime());
}