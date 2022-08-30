#define _CRT_SECURE_NO_WARNINGS
#define KB 1024
#include <stdlib.h>
#include <stdio.h>
#include "dictionary.h"
#include "binaryFile.h"
#include "filesHandling.h"
#include "detailsStruct.h"
#include "compare.h"
#include "log.h"
extern struct Details* details;

Sequence* replaceAppendSequence(Sequence* s, unsigned char c) {
	Sequence* temp = copySequenceAppend(s, c);
	deleteSequence(s);

	return temp;
}
//initialize a dictionary:
//first 256 places for ascii code
Dict* initializeDict(unsigned int size) {

	Dict* dict = newDict(size);

	for (unsigned int i = 0; i < 256; i++) {
		Sequence* sequence = newSequence((unsigned char)i);
		insertDict(dict, sequence, i);
	}
	return dict;
}


int compression(FILE* fpSource, FILE* fpOutput) {
	LOG_INFO(__func__,"The compression process starts")
	//store the next character/byte
	unsigned int character;
	//will be the output eventually
	unsigned int code;
	//buffer for reading input file
	unsigned char inputBuffer[KB];
	unsigned char outputBuffer[KB];
	//initialize the table for 12 bits
	unsigned int tableSize = 1 << 16;
	Dict* dict = initializeDict(tableSize);
	//keep track of table entries
	int nextCode = 256, flag = 0;
	int indInputBuffer = 0, indOutputBuffer = 0;
	int fileSize = findSize(fpSource);
	int cnt = fread(inputBuffer, 1, KB, fpSource);
	if (cnt < KB)
		flag = 1;
	character = inputBuffer[indInputBuffer++];
	int chunk;
	Sequence* str = newSequence(character);
	chunk = flag ? cnt : cnt;
	//chunk = flag ? (fileSize % KB) : KB;
	//streaming the data
	while (cnt >= KB || flag) {
		character = inputBuffer[indInputBuffer++];
		if (indInputBuffer == chunk) {
			if (!flag) {
				indInputBuffer = 0;
				cnt = fread(inputBuffer, 1, chunk, fpSource);
				if (cnt < chunk) {
					flag = 1;
					chunk = cnt;
					//chunk = (fileSize % KB);
				}
				else
					chunk = KB;
			}
			else
			{
				flag = 0;
			}
		}
		Sequence* expandedStr = copySequenceAppend(str, character);
		//if sequence is in the dict
		if (searchDict(dict, expandedStr, &code)) {
			deleteSequence(str);
			str = expandedStr;
		}
		//sequence is not in dict
		else {
			//searching without the next character
			searchDict(dict, str, &code);
			//output 
			// the code
			write16bitsToBuffer(outputBuffer, indOutputBuffer, code);
			if (indOutputBuffer == KB - 2) {
				fwrite(outputBuffer, KB, 1, fpOutput);
				indOutputBuffer = 0;
			}
			else
				indOutputBuffer += 2;
			//write16bits(fpOutput, code);
			/*if (nextCode >= (1 << (bits)) && bits < maxBits) {
				bits++;
			}*/
			//check table size. if it's okay, insert to dict
			if (nextCode < tableSize) {
				insertDict(dict, expandedStr, nextCode++);

			}
			//stop creating new entries
			else {
				deleteSequence(expandedStr);
			}
			deleteSequence(str);
			str = newSequence(character);
		}
	}
	searchDict(dict, str, &code);
	write16bitsToBuffer(outputBuffer, indOutputBuffer, code);
	fwrite(outputBuffer, indOutputBuffer + 2, 1, fpOutput);
	//write16bits(fpOutput, code);
	/*writeBinary(fpOutput, code);*/
	deleteSequence(str);
	deleteDictDeep(dict);

	//decompression
	//comparison
	details->outputFileSize = findSize(fpOutput);
	LOG_INFO(__func__,"Compression completed successfully")
	//close the files
	if (closeFile(fpSource)) {
		LOG_INFO(__func__,"The source file closed successfully")
		if (closeFile(fpOutput)) {
			LOG_INFO(__func__,"The compressed file closed successfully")
			return wrapCompare();


		}
		return 0;
	}
}
