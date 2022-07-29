#define _CRT_SECURE_NO_WARNINGS
#include "dictionary.h"
#include "compare.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "binaryFile.h"
#include "detailsStruct.h"
#define maxBits 12

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

//for the logging file
extern struct Details details;
void compression(FILE* fpSource, FILE* fpOutput) {
	//store the next character/byte
	unsigned char character;
	//will be the output eventually
	unsigned int code;
	//initialize the table for 12 bits
	unsigned int tableSize = 1 << maxBits;
	Dict* dict = initializeDict(tableSize);
	//keep track of table entries
	int nextCode = 256;
	character = getc(fpSource);
	Sequence* str = newSequence(character);
	//or c!=-1?
	while (character != EOF) {
		character = getc(fpSource);
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
			writeBinary(fpOutput, code);
			/*if (nextCode >= (1 << (bits)) && bits < maxBits) {
				bits++;
			}*/
			//check table size if it's okay, insert to dict
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
	writeBinary(fpOutput, code);
	deleteSequence(str);
	deleteDictDeep(dict);
	//close output file
	//decompression
	//comparison

}







