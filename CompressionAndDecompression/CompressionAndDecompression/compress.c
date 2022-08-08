#define _CRT_SECURE_NO_WARNINGS
#include "dictionary.h"
#include "compress.h"
#include "binaryFile.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "filesHandling.h"
#include "detailsStruct.h"
#include "compare.h"
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
	time_t t = time(NULL);
	struct tm* tm = localtime(&t);
	ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "The compression process starts at: %s.\n", asctime(tm));
	//store the next character/byte
	unsigned int character;
	//will be the output eventually
	unsigned int code;
	//initialize the table for 12 bits
	unsigned int tableSize = 1 << 16;
	Dict* dict = initializeDict(tableSize);
	//keep track of table entries
	int nextCode = 256;
	character = getc(fpSource);
	Sequence* str = newSequence(character);

	//streaming the data
	while (character != EOF) {
		character = getc(fpSource);
		Sequence* expandedStr = copySequenceAppend(str, character);
		puts(expandedStr->data);

		//if sequence is in the dict
		if (searchDict(dict, expandedStr, &code)) {
			deleteSequence(str);
			str = expandedStr;
			puts(str->data);
		}
		//sequence is not in dict
		else {
			//searching without the next character
			searchDict(dict, str, &code);
			//output 
			// the code
			write16bits(fpOutput, code);
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
	/*writeBinary(fpOutput, code);*/
	deleteSequence(str);
	deleteDictDeep(dict);

	//decompression
	//comparison
	t = time(NULL);
	tm = localtime(&t);
	ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "Compression completed successfully at: %s.\n", asctime(tm));
	//close the files
	if (closeFile(fpSource)) {
		ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "The source file closed successfully\n");
		if (closeFile(fpOutput)) {
			ENABLE_DEBUG_LOG&& fprintf(details->fpLogFile, "The compressed file closed successfully\n");
			return wrapCompare();
			
			
		}
		return 0;
	}
}
