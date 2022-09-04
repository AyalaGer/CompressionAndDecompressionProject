#define _CRT_SECURE_NO_WARNINGS
#define K_BUFFER_SIZE 1024
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "decompress.h"
#include "detailsStruct.h"
#include "filesHandling.h"
#include "log.h"
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

	if (openFile(pathOutputDecompression, &fpOutputDecompression, "a+") == SUCCESS) {
		//Call the decompression function
		int decompressionResult = decompression(fpCompressed, fpOutputDecompression);
		//Check if the decompression proccess completed successfuly. and print the status to the log file.
		if (decompressionResult ==FAILURE) {
			//print to log file
			 LOG_INFO(__func__,"Decompression in comparison failed")
			return FAILURE;
		}
		//print to log file
		
		return SUCCESS;
	}
	else {
		//print to log file
		return FAILURE;
	}
}

int areFileSizesEquals() {
	//set the files size to variables
	int decompressedFileSize = findSize(fpOutputDecompression);
	int sourceFileSize = details->inputFileSize;
	if (sourceFileSize == decompressedFileSize) {
		//print to log file
		LOG_INFO(__func__,"The size of both files are the same")
		return SUCCESS;
	}
	//print to log file
	LOG_INFO(__func__,"File sizes are not equal - Comparison proccess failed")
	return FAILURE;
}

int kComparison(FILE* fpSource, unsigned char fpSourceKBuffer[K_BUFFER_SIZE], unsigned char fpDecompressedKBuffer[K_BUFFER_SIZE], int fileSize) {
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
		if (strncmp((const char*)fpSourceKBuffer, (const char*)fpDecompressedKBuffer, amountCompare) != 0) {
			//Close the decompressed file before the remove. (?) ask if success
			closeFile(fpOutputDecompression);
			//Remove the decompressed file.
			removeFile(pathOutputDecompression);
			return FAILURE;
		}
	} while (countInSurceFile);
	//Close the decompressed file before the remove. (?) ask if success
	//closeFile(fpOutputDecompression);
	//remove the decompressed file.
	//removeFile(pathOutputDecompression);
	return SUCCESS;
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
		if (kComparison(fpSouce, fpSourceKBuffer, fpDecompressedKBuffer, sizeFile) != SUCCESS) {
			//print to log file
			LOG_INFO(__func__,"The files are not equal")
			return FAILURE;
		}
	}

	//the file size is not correct.
	else {
		//print to log file
		//ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "the size files is not correct! at: %s.", calcTime());
		return FAILURE;
	}
	//print to log file
	LOG_INFO(__func__,"The files are equal. Comparison process completed successfully")
	return SUCCESS;
}

int wrapCompare()
{
	//Define two parameters:fpCompressed - a pointer to the compressed file and fpSource - pointer
	// to the source file.
	FILE* fpSource = NULL, * fpCompressed = NULL;	
	//Print to the log file the comparison process has begun.
	LOG_INFO(__func__,"Comparison started")
	//Open files and prints the status to the log file.
		if (openFile(details->inputFilePath, &fpSource, "r") == SUCCESS) {
			if (openFile(details->outputFilePath, &fpCompressed, "rb") == SUCCESS) {
				//Start decompression proccess.
				int wrapDecompressionResult = wrapDecompression(fpCompressed);
				//Check if the decompression proccess failed.
				if (wrapDecompressionResult == FAILURE) {
					LOG_INFO(__func__, "Parsing decompression failed")
						//remove the decompressed file 
						removeFile(pathOutputDecompression);
					return FAILURE;
				}
				if (openFile(pathOutputDecompression, &fpOutputDecompression, "r")==FAILURE) {
					LOG_INFO(__func__, "unable to open the comparison file")
						return FAILURE;
				}

				//check if the files size are the same and continue only if it is.
				if (areFileSizesEquals() == SUCCESS) {
					//Define the buffers with the relevant size.
					unsigned char fpSourceKBuffer[K_BUFFER_SIZE]; // 1 kB buffer for the fpSource.
					unsigned char fpDecompressedKBuffer[K_BUFFER_SIZE]; // 1 kB buffer for the fpDecompressed.
					if (kComparison(fpSource, fpSourceKBuffer, fpDecompressedKBuffer, details->inputFileSize)==SUCCESS) {
						LOG_INFO(__func__, "comparison completed successfully")
						return SUCCESS;
					}
				}
				LOG_INFO(__func__, "Comparison failed")
					return FAILURE;
			}
			else {
				LOG_INFO(__func__, "unable to open the output file")
					return FAILURE;
			}
		}
		else {
			LOG_INFO(__func__, "unable to open the source file")
				return FAILURE;
		}
}
