#include "pch.h"
#include "../CompressionAndDecompression/parsing.h"
#include "../CompressionAndDecompression/parsing.c"
#include "../CompressionAndDecompression/filesHandling.h"
#include "../CompressionAndDecompression/filesHandling.c"
#include "../CompressionAndDecompression/compress.h"
#include "../CompressionAndDecompression/decompress.h"
#include "../CompressionAndDecompression/compress.c"
#include "../CompressionAndDecompression/decompress.c"
#include  "../CompressionAndDecompression/Sequence.h"
#include  "../CompressionAndDecompression/Sequence.c"
#include  "../CompressionAndDecompression/detailsStruct.h"
#include  "../CompressionAndDecompression/detailsStruct.c"
#include  "../CompressionAndDecompression/dictionary.h"
#include  "../CompressionAndDecompression/dictionary.c"
#include  "../CompressionAndDecompression/binaryFile.h"
#include  "../CompressionAndDecompression/binaryFile.c"
#include "../CompressionAndDecompression/array.h"
#include "../CompressionAndDecompression/array.c"
#include "../CompressionAndDecompression/compare.h"
#include "../CompressionAndDecompression/compare.c"


extern Details* details;

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

//Open files
TEST(FileHandling, OpenFile) {
	FILE* fp;
	char* path = "txt.txt";
	char* path1 = "txt1.txt";
	//Open a valid file.
	EXPECT_EQ(1, openFile(path, &fp, "a+"));
	//Open an unexisting file in read mode.
	EXPECT_EQ(0, openFile(path1, &fp, "r"));
	//Open an invalid file.
	EXPECT_EQ(0, openFile("C:\\Users\\Efrat\\Downloading\\short.txt", &fp, "a+"));
}
TEST(FileHandling, CloseFile) {
	FILE* fp;
	char* path = "txt.txt";
	char* path1 = "txt1.txt";
	openFile(path, &fp, "a+");
	//Close a valid file.
	EXPECT_EQ(1, closeFile(fp));
	//Close closed file
	EXPECT_EQ(0, closeFile(fp));
}

TEST(FileHandling, RemoveFile) {
	//remove opened file
	FILE* fp;
	char* path = "remove.txt";
	openFile(path, &fp, "a+");
	EXPECT_EQ(0, removeFile(path));
	//remove unexists file
	EXPECT_EQ(0, removeFile("dfhh.txt"));
	//remove valid file
	closeFile(fp);
	EXPECT_EQ(1, removeFile(path));
}
TEST(parsingArguments, checKLimitFileSize) {
	details = allocateDetails();
	//check the limit of file size
	char* path= "C:\\Users\\מירי\\Downloads\\omlyTest.txt", * mode="compression";
	EXPECT_EQ(0, parsing(path, mode));
	

}
TEST(parsingArguments, checkMode) {
	details = allocateDetails();
	//check the mode passed from the user- compression/decompression/other
	EXPECT_EQ(0, parsing("D:\\short.txt", "comparison"));
}
TEST(parsingArguments, checkIfExistAndRename) {
	details = allocateDetails();
	//Rename output file if a file with that name exists	
	EXPECT_TRUE(0 == strcmp("C:\\Users\\מירי\\Desktop\\קובצי טקסט דיני\\short-copy.txt", checkAndChangeOutputPath("C:\\Users\\מירי\\Desktop\\קובצי טקסט דיני\\short.txt", ".txt")));
	//No change to the file name if a file with that name does not already exist
	EXPECT_TRUE(0!= strcmp("C:\\Users\\מירי\\Desktop\\קובצי טקסט דיני\\dini-copy.txt", checkAndChangeOutputPath("C:\\Users\\מירי\\Desktop\\קובצי טקסט דיני\\dini.txt", ".txt")));

}

TEST(parsingArguments, checkExtension) {
	details = allocateDetails();
	//check the extension of the source file if it is valid
	EXPECT_EQ(0, parsing("D:\\short.lzw", "compression"));
	EXPECT_EQ(0, parsing("D:\\short.txt", "decompression"));
}

TEST(decompress, checkIfEmpty) {
	details = allocateDetails();
	//check if the compressed file is empty
	FILE* fpIn, * fpOut;
	if (openFile("D:\\קבצי טקסט\\empty.bin", &fpIn, "r") &&
		openFile("D:\\קבצי טקסט\\decompressed.txt", &fpOut, "a+")) {
		EXPECT_EQ(0, decompression(fpIn, fpOut));
	}
}


//decompression:
//1. check if decompressed file is empty-V
//2. check if the array full-I think it's unnecessary

//other:
//1. remove file checking -v
//2. open file without open pwemission
//3. add cases in close file- v


//main():
//check the numbers of arguments
// lzw, calculations
//there is if but not something special to check
//dictionary, compress, compare



