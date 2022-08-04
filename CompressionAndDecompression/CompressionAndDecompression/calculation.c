#include "detailsStruct.h"
#include <time.h>
extern struct Details* details;

double compressionRatio(int inFSize, int outFSize)
{
	return inFSize / outFSize;
}

long runningTime()
{
	time_t current_time;
	time(&current_time);
	return current_time - details->startTime;

}
void calculation(char* mode)
{
	fprintf(details->fpLogFile, "calculation process has begun at: %ld.", time(NULL));
	if (strcmp(mode, "compression")) {
		double ratio = compressionRatio(details->inputFileSize, details->outputFileSize);
		printf("%d", ratio);
		long time = runningTime();
		printf("%d", time);
	}
	else if (strcmp(mode, "decompression")) {
		long time = runningTime();
		printf("%d", time);
	}
	else {
		ptintf("ERROR!");
	}
	fprintf(details->fpLogFile, "calculation process complited successfully at: %ld.", time(NULL));
}