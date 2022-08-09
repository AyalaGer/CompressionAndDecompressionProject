#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "detailsStruct.h"

struct Details* allocateDetails() {
	struct Details* details = (struct Details*)malloc(sizeof(struct Details));
	return details;
}

//function to calculate the current time.
char* calcTime() {
	time_t t = time(NULL);
	struct tm* tm = localtime(&t);
	char* date = asctime(localtime(&t));
	date[strlen(date) - 1] = '\0';
	return date;
}
