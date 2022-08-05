#define _CRT_SECURE_NO_WARNINGS
#define K_BUFFER_SIZE 1024
#define M_BUFFER_SIZE 1024*1024
#include "compress.h"
#include "decompress.h"
#include "compare.h"
#include "detailsStruct.h"
#include "filesHandling.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//setting global variables.

//to get the global array.
extern struct Details* details;

//pointer to the  decompressed file.
FILE* fpOutputDecompression;

//path to the  decompressed file.
char* pathOutputDecompression = "outputDecompression.txt";

//for knowing in error case the position thet the error occured.
int position = 0;



//function to calculate the file size to verify which effective 'over on the file' to perform -
//(over character character or over kilobyte kilobyte or megabyte megabyte).
int fileSize(FILE* fp) {
	// seek to end of file.
	fseek(fp, 0, SEEK_END);
	// get current file pointer.
	int	size = ftell(fp);
	// seek back to beginning of file.
	fseek(fp, 0, SEEK_SET);
	return size;
}

//function for the decompression proccess.
int wrapDecompression(FILE* fpCompressed) {
	//open the output Decompression file and print the status to the log file.

	if (openFile(pathOutputDecompression, fpOutputDecompression, "a+") == 1) {
		//Call the decompression function
		int decompressionResult = decompression(fpCompressed, fpOutputDecompression);
		//check if the decompression proccess completed successfuly. and print the status to the log file.
		if (decompressionResult != 1) {
			//print to log file
			fprintf(details->fpLogFile, "decompression in the comparison process failed at: %s.", calcTime());
			return 0;
		}
		//print to log file
		fprintf(details->fpLogFile, "decompression in the comparison process completed successfuly at:  %s.", calcTime());
		return 1;
	}
	else {
		//print to log file
		fprintf(details->fpLogFile, "Unable to open the empty output decompression file at:  %s.", calcTime());
		return 0;
	}
}

int areFileSizesEquals(int sourceFileSize, int decompressedFileSize) {
	if (sourceFileSize == decompressedFileSize) {
		//print to log file
		fprintf(details->fpLogFile, "the size files are equals!!! at: %s.", calcTime());
		return 1;
	}
	//print to log file
	fprintf(details->fpLogFile, "the size files are not equals - the comparison proccess failed at:  %s.", calcTime());
	return 0;
}


//int chComparison(FILE* fpSource) {
//	char chInSurceFile = getc(fpSource);
//	char chInDecompressedFile = getc(fpOutputDecompression);
//	// over on the file character character untill the end of file.
//	while (chInSurceFile != EOF && chInDecompressedFile != EOF) {
//		//check if the characters are not the same.
//		if (chInSurceFile != chInDecompressedFile) {
//			//remove the decompressed file 
//			removeFile(pathOutputDecompression);
//			return 0;
//		}
//		//continue only if the characters are the same.
//		position++;
//		chInSurceFile = getc(fpSource);
//		chInDecompressedFile = getc(fpOutputDecompression);
//	}
//	//remove the decompressed file 
//	removeFile(pathOutputDecompression);
//	return 1;
//}


int kComparison(FILE* fpSource, unsigned char fpSourceKBuffer[], unsigned char fpDecompressedKBuffer[], int fileSize) {

	int countInSurceFile;
	int countInDecompressedFile;
	//over on the files kilobyte kilobyte untill comming to the end of file.

	int amountCompare;
	do
	{
		countInSurceFile = fread(fpSourceKBuffer, 1024, 1, fpSource);
		countInDecompressedFile = fread(fpDecompressedKBuffer, 1024, 1, fpOutputDecompression);
		amountCompare = countInSurceFile ? 1024 : (fileSize % 1024);
		if (strncmp(fpSourceKBuffer, fpDecompressedKBuffer, amountCompare) != 0) {
			//remove the decompressed file.
			removeFile(pathOutputDecompression);
			return 0;
		}
	} while (countInSurceFile);
	//remove the decompressed file.
	removeFile(pathOutputDecompression);
	return 1;
}

int goToTheRelevantComparison(int sizeFile, FILE* fpSouce, FILE* fpDeconpressed) {
	////check if effective to over character character.
	//if (sizeFile > 0 && sizeFile < 1024) {
	//	if (chComparison(fpSouce, fpDeconpressed) != 1) {
	//		//print to log file
	//		fprintf(details->fpLogFile, "the chComparison not successes! at:  %s.", calcTime());
	//		return 0;
	//	}
	//}
	//check if effective to over kilobyte kilobyte.
	if (sizeFile > 0) {
		unsigned char fpSourceKBuffer[K_BUFFER_SIZE]; // 1 kB buffer for the fpSource.
		unsigned char fpDecompressedKBuffer[K_BUFFER_SIZE]; // 1 kB buffer for the fpDecompressed.
		if (kComparison(fpSouce, fpSourceKBuffer, fpDecompressedKBuffer, sizeFile) != 1) {
			//print to log file
			fprintf(details->fpLogFile, "the kComparison not successes! at: %s.", calcTime());
			return 0;
		}
	}

	//the file size is not correct.
	else {
		//print to log file
		fprintf(details->fpLogFile, "the size files is not correct! at: %s.", calcTime());
		return 0;
	}
	//print to log file
	fprintf(details->fpLogFile, "comparison process complited successfully at:  %s.", calcTime());
	return 1;
}

int wrapCompare(FILE* fpSource, FILE* fpCompressed)
{
	//The function gets two parameters:fpCompressedFile - a pointer to the compressed file and fpSource - pointer
	// to the source file.

	//Print to the log file the comparison process has begun.
	fprintf(details->fpLogFile, "comparison process has begun at:  %s.", calcTime());


	//open files and prints the status to the log file.
	if (openFile(details->inputFilePath, fpSource, "r") == 1 && openFile(details->outputFilePath, fpCompressed, "a+") == 1) {
		//start decompression proccess.
		int wrapDecompressionResult = wrapDecompression(fpCompressed);
		//check if the decompression proccess failed.
		if (wrapDecompressionResult == 0) {
			fprintf(details->fpLogFile, "The shell decompression in the comparison process failed at:  %s.", calcTime());
			//remove the decompressed file 
			removeFile(pathOutputDecompression);
			return 0;
		}
		//continue if the decompression proccess completed successfuly.
		//set the files size to variables
		int decompressedFileSize = fileSize(fpOutputDecompression);
		int sourceFileSize = details->inputFileSize;
		//check if the files size are the same and continue only if it is.
		if (areFileSizesEquals(decompressedFileSize, sourceFileSize) == 1) {
			//continue only if the goToTheRelevantComparison successfuly
			if (goToTheRelevantComparison(sourceFileSize, fpSource, fpOutputDecompression) == 1) {
				//print to log file
				fprintf(details->fpLogFile, "The comparison proccess successful on the edge way!!!!!!!!!!!!! at:  %s.", calcTime());
				return 1;
			}
			//print to log file
			fprintf(details->fpLogFile, "The comparison proccess does not successful on the edge way!!!!!!!!!!!!! at:  %s.", calcTime());
			return 0;
		}
		//print to log file
		fprintf(details->fpLogFile, "The comparison proccess does not successful on the edge way!!!!!!!!!!!!! at:  %s.", calcTime());
		return 0;
	}
	else if (openFile(details->inputFilePath, fpSource, "r") == 1 && openFile(details->outputFilePath, fpCompressed, "a+") == 0) {
		//print to log file
		fprintf(details->fpLogFile, "Unable to open the compressed file at:  %s.", calcTime());
	}
	else if (openFile(details->inputFilePath, fpSource, "r") == 0 && openFile(details->outputFilePath, fpCompressed, "a+") == 1) {
		//print to log file
		fprintf(details->fpLogFile, "Unable to open the source file at:  %s.", calcTime());
	}
	else {
		//print to log file
		fprintf(details->fpLogFile, "Unable to open the compressed file and the source file at:  %s.", calcTime());
	}
}
