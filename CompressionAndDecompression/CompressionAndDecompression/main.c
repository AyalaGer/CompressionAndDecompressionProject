#define _CRT_SECURE_NO_WARNINGS
#include "compare.h"
#include "compress.h"
#include "decompress.h"
#include "parsing.h"
#include "lzwCompressionDecompression.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "detailsStruct.h"




struct Details details;

void main(/*int argc, char* argv[]*/)
{
	/*char* path = "source.txt";
	char* mode = "compress";*/
	if(argc>1)
		lzwCompressionDecompression(argv[1], argv[2]);
	else
		printf("enter file path and mode:\n");
	
	//char* write = "a+";
	//if (argc == 1)
	//	printf("hello perfect project main - not parameters inserted");
	//else if (argv[1]) {
	//	//Console.WriteLine(argv[1]);
	//	FILE* demo = fopen(argv[1], write);
	//	fprintf(demo, "%s %s %s", "loves", "the", "life!!!!!!!!!!!");
	//	fclose(demo);
	//	FILE* demoo;
	//	int display;
	//	demo = fopen(argv[1], "r");
	//	while (1) {
	//		display = fgetc(demo);
	//		if (feof(demo))
	//			break;
	//		printf("%c", display);
	//	}
	//	fclose(demo);
	//}
	//else if (argv[2]) {
	//}
}

