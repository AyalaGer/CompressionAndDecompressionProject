#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "lzwCompressionDecompression.h"
#include "detailsStruct.h"

extern struct Details* details;

void main(/*int argc, char* argv[]*/)
{
	
	details = allocateDetails();
	 
	//char* path = "C:\\Users\\WIN 10\\Desktop\\filePath2.bin";
	//char* path = "C:\\Users\\WIN 10\\Desktop\\short.txt";
	char* path = "C:\\Users\\WIN 10\\Desktop\\קבצי טקסט\\duplicate.txt";
	//char* path = "C:\\Users\\WIN 10\\Desktop\\source (1).txt";
	//char* path = "C:\\Users\\WIN 10\\Downloads\\source (1).lzw";
	char* path = "C:\\אילה\\בוטקמפ\\ווסטרן דיגיטל בוטקמפ\\project\\קבצים לדוגמא לפרויקט\\ניסוי.txt";
	char* mode = "compression";
	lzwCompressionDecompression(path, mode);
	/*if(argc>1)
		lzwCompressionDecompression(argv[1], argv[2]);
	else
		printf("enter file path and mode:\n");*/
}

