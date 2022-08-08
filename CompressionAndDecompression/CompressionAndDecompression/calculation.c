#include "detailsStruct.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
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
	ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "calculation process has begun at: %s.",calcTime());
	if (!strcmp(mode, "compression")) {
		double ratio = compressionRatio();
		ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "The compression ratio is %f\n", ratio);
		printf("The compression ratio is %f\n", ratio);
		long time = runningTime();
		ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "the running time of %s is %ld", mode, time);
		printf("The running time of %s is %ld",mode,time);
	}
	else {
		long time = runningTime();
		ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "the running time of %s is %ld", mode, time);
		printf("The running time of %s is %ld", mode, time);
	}
	ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "Calculation process complited successfully at: %s.", calcTime());
}