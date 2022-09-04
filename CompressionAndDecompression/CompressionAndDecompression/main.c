#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "lzwCompressionDecompression.h"
#include "detailsStruct.h"

extern struct Details* details;

void main(int argc, char* argv[])
{
	printf("dgfgfg");
	//allocate a memory for the global struct
	details = allocateDetails();
	
	lzwCompressionDecompression(argv[1], argv[2]);
	if(argc>1)
		lzwCompressionDecompression(argv[1], argv[2]);
	else
		printf("enter file path and mode:\n");
}

