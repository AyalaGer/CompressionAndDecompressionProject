#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "detailsStruct.h"
#include "log.h"
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
	LOG_INFO(__func__,"Calculation started")
	if (!strcmp(mode, "compression")) {
		double ratio = compressionRatio();
		LOG_INFO(__func__, "Print the compression ratio to the user")
		printf("The compression ratio is %f\n", ratio);
		double time = runningTime();
		LOG_INFO(__func__,"Print the running time")
		printf("The running time of %s is %f\n",mode,time);
	}
	else {
		double time = runningTime();
		LOG_INFO(__func__, "Print the running time")
		printf("The running time of %s is %f", mode, time);
	}
	LOG_INFO(__func__, " Calculation process completed successfully")
}