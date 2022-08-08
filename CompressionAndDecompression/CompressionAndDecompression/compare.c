#define _CRT_SECURE_NO_WARNINGS
#define K_BUFFER_SIZE 1024
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "decompress.h"
#include "detailsStruct.h"
#include "filesHandling.h"

//Setting global variables.

//To get the global array.
extern struct Details* details;

//Pointer to the  decompressed file.
FILE* fpOutputDecompression;

//Path to the  decompressed file.
char* pathOutputDecompression = "outputDecompression.txt";

//For knowing in error case the position that the error occured.
int position = 0;

//Function for the decompression proccess.
int wrapDecompression(FILE* fpCompressed) {
	//Open the output Decompression file and print the status to the log file.

	if (openFile(pathOutputDecompression, &fpOutputDecompression, "a+") == 1) {
		//Call the decompression function
		int decompressionResult = decompression(fpCompressed, fpOutputDecompression);
		//Check if the decompression proccess completed successfuly. and print the status to the log file.
		if (decompressionResult != 1) {
			//print to log file
			ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "decompression in the comparison process failed at: %s.", calcTime());
			return 0;
		}
		//print to log file
		ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "decompression in the comparison process completed successfuly at:  %s.", calcTime());
		return 1;
	}
	else {
		//print to log file
		ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "Unable to open the empty output decompression file at:  %s.", calcTime());
		return 0;
	}
}

int areFileSizesEquals() {
	//set the files size to variables
	int decompressedFileSize = findSize(fpOutputDecompression);
	int sourceFileSize = details->inputFileSize;
	if (sourceFileSize == decompressedFileSize) {
		//print to log file
		ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "the size files are equals!!! at: %s.", calcTime());
		return 1;
	}
	//print to log file
	ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "the size files are not equals - the comparison proccess failed at:  %s.", calcTime());
	return 0;
}


//int chComparison(FILE* fpSource) {
//	char chInSurceFile = getc(fpSource);
//	char chInDecompressedFile = getc(fpOutputDecompression);
//	// Over on the file character character untill the end of file.
//	while (chInSurceFile != EOF && chInDecompressedFile != EOF) {
//		//check if the characters are not the same.
//		if (chInSurceFile != chInDecompressedFile) {
//			//Remove the decompressed file 
//			removeFile(pathOutputDecompression);
//			return 0;
//		}
//		//Continue only if the characters are the same.
//		position++;
//		chInSurceFile = getc(fpSource);
//		chInDecompressedFile = getc(fpOutputDecompression);
//	}
//	//Remove the decompressed file 
//	removeFile(pathOutputDecompression);
//	return 1;
//}


int kComparison(FILE* fpSource, unsigned char fpSourceKBuffer[], unsigned char fpDecompressedKBuffer[], int fileSize) {
	//Define the variables for the result from the fread function.
	int countInSurceFile;
	int countInDecompressedFile;
	//Define the variable for knowing how many characters to compare in the last interation.
	int amountCompare;
	//Over on the files kilobyte kilobyte untill comming to the end of file.
	do
	{
		//Read kilobyte characters from the source file.
		countInSurceFile = fread(fpSourceKBuffer, K_BUFFER_SIZE, 1, fpSource);
		//Read kilobyte characters from the decompressed file.
		countInDecompressedFile = fread(fpDecompressedKBuffer, K_BUFFER_SIZE, 1, fpOutputDecompression);
		//Calculate how many rest in the last buffer.
		amountCompare = countInSurceFile ? K_BUFFER_SIZE : (fileSize % K_BUFFER_SIZE);
		//Comparison if are the chunks the same.
		if (strncmp(fpSourceKBuffer, fpDecompressedKBuffer, amountCompare) != 0) {
			//Close the decompressed file before the remove. (?) ask if success
			closeFile(fpOutputDecompression);
			//Remove the decompressed file.
			removeFile(pathOutputDecompression);
			return 0;
		}
	} while (countInSurceFile);
	//Close the decompressed file before the remove. (?) ask if success
	//closeFile(fpOutputDecompression);
	//remove the decompressed file.
	//removeFile(pathOutputDecompression);
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
		//Define the buffers with the relevant size.
		unsigned char fpSourceKBuffer[K_BUFFER_SIZE]; // 1 kB buffer for the fpSource.
		unsigned char fpDecompressedKBuffer[K_BUFFER_SIZE]; // 1 kB buffer for the fpDecompressed.
		if (kComparison(fpSouce, fpSourceKBuffer, fpDecompressedKBuffer, sizeFile) != 1) {
			//print to log file
			ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "the kComparison not successes! at: %s.", calcTime());
			return 0;
		}
	}

	//the file size is not correct.
	else {
		//print to log file
		ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "the size files is not correct! at: %s.", calcTime());
		return 0;
	}
	//print to log file
	ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "comparison process complited successfully at:  %s.", calcTime());
	return 1;
}

int wrapCompare()
{
	//Define two parameters:fpCompressed - a pointer to the compressed file and fpSource - pointer
	// to the source file.
	FILE* fpSource = NULL, * fpCompressed = NULL;
	
	//Print to the log file the comparison process has begun.
	ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "comparison process has begun at:  %s.", calcTime());


	//Open files and prints the status to the log file.
	if (openFile(details->inputFilePath, &fpSource, "r") == 1 && openFile(details->outputFilePath, &fpCompressed, "rb") == 1) {
		//Start decompression proccess.
		int wrapDecompressionResult = wrapDecompression(fpCompressed);
		//Check if the decompression proccess failed.
		if (wrapDecompressionResult == 0) {
			ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "The shell decompression in the comparison process failed at:  %s.", calcTime());
			//remove the decompressed file 
			removeFile(pathOutputDecompression);
			return 0;
		}
		openFile(pathOutputDecompression, &fpOutputDecompression, "r");
		//continue if the decompression proccess completed successfuly.
		
		//check if the files size are the same and continue only if it is.
		if (areFileSizesEquals() == 1) {
			//continue only if the goToTheRelevantComparison successfuly
			if (goToTheRelevantComparison(details->inputFileSize, fpSource, fpOutputDecompression) == 1) {
				//print to log file
				ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "The comparison proccess successful on the edge way!!!!!!!!!!!!! at:  %s.", calcTime());
				return 1;
			}
			//print to log file
			ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "The comparison proccess does not successful on the edge way!!!!!!!!!!!!! at:  %s.", calcTime());
			return 0;
		}
		//print to log file
		ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "The comparison proccess does not successful on the edge way!!!!!!!!!!!!! at:  %s.", calcTime());
		return 0;
	}
	else if (openFile(details->inputFilePath, fpSource, "r") == 1 && openFile(details->outputFilePath, fpCompressed, "a+") == 0) {
		//print to log file
		ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "Unable to open the compressed file at:  %s.", calcTime());
	}
	else if (openFile(details->inputFilePath, fpSource, "r") == 0 && openFile(details->outputFilePath, fpCompressed, "a+") == 1) {
		//print to log file
		ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "Unable to open the source file at:  %s.", calcTime());
	}
	else {
		//print to log file
		ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "Unable to open the compressed file and the source file at:  %s.", calcTime());
	}
}
