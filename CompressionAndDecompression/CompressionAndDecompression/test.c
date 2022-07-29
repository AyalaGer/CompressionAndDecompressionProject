#include <stdio.h>
#include <stdlib.h>
#include "detailsStruct.h"
extern struct Details details;
int closeFile(FILE* fp) {
	if (fclose(fp) == 0) {
		fprintf(details.fpLogFile, "File closed successfully");
		return 1;
	}
	else {
		fprintf(details.fpLogFile, "Unable to close the file");
		return 0;
	}
}

//int checkTableSize();