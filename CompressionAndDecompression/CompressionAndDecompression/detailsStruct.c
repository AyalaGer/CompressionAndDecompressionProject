#include "detailsStruct.h"
#include <stdio.h>
#include <stdlib.h>
struct Details* allocateDetails() {
	struct Details* details = (struct Details*)malloc(sizeof(struct Details));
	return details;
}
