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
void calculation()
{
	double ratio = compressionRatio(details->inputFileSize, details->outputFileSize);
	long time = runningTime();
	//return the results to the command line.
}