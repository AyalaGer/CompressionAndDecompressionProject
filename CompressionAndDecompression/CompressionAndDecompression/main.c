#define _CRT_SECURE_NO_WARNINGS
//#include "compare.h"
//#include "compress.h"
//#include "decompress.h"
//#include "parsing.h"
#include "lzwCompressionDecompression.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "detailsStruct.h"
extern struct Details* details;





void main(/*int argc, char* argv[]*/)
{
	
	details = allocateDetails();
	printf("hello");
	char* path = "C:\\Users\\WIN 10\\Downloads\\source (1).txt";
	char* mode = "compression";
	lzwCompressionDecompression(path, mode);
	/*if(argc>1)
		lzwCompressionDecompression(argv[1], argv[2]);
	else
		printf("enter file path and mode:\n");*/
}

