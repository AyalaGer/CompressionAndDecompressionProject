#include <stdio.h>
#include <stdlib.h>


int closeFile(FILE* fp) {
	if (fclose(fp) == 0) 
		return 1;
	
	else 
		return 0;
	
}

