#include "detailsStruct.h"
#include <stdio.h>
#include <stdlib.h>
struct Details* allocateDetails() {
	struct Details* details = (struct Details*)malloc(sizeof(struct Details));
	return details;
}

//function to calculate the current time.
char* calcTime() {
	time_t t = time(NULL);
	struct tm* tm = localtime(&t);
	return asctime(tm);
}
