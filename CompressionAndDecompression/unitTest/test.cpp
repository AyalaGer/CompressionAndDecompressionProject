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
	EXPECT_EQ(SUCCESS, openFile(path, &fp, "a+"));
	//Open an unexisting file in read mode.
	EXPECT_EQ(FAILURE, openFile(path1, &fp, "r"));
	//Open an invalid file.
	EXPECT_EQ(FAILURE, openFile("C:\\Users\\Efrat\\Downloading\\short.txt", &fp, "a+"));
}
TEST(FileHandling, CloseFile) {
	FILE* fp;
	char* path = "txt.txt";
	char* path1 = "txt1.txt";
	openFile(path, &fp, "a+");
	//Close a valid file.
	EXPECT_EQ(SUCCESS, closeFile(fp));
	//Close closed file
	EXPECT_EQ(FAILURE, closeFile(fp));
}

TEST(FileHandling, RemoveFile) {
	//remove opened file
	FILE* fp;
	char* path = "remove.txt";
	openFile(path, &fp, "a+");
	EXPECT_EQ(FAILURE, removeFile(path));
	//remove unexists file
	EXPECT_EQ(FAILURE, removeFile("dfhh.txt"));
	//remove valid file
	closeFile(fp);
	EXPECT_EQ(SUCCESS, removeFile(path));
}
TEST(parsingArguments, checKLimitFileSize) {
	details = allocateDetails();
	//check the limit of file size
	char* path= "C:\\Users\\îéøé\\Downloads\\omlyTest.txt", * mode="compression";
	EXPECT_EQ(FAILURE, parsing(path, mode));
	

}
TEST(parsingArguments, checkMode) {
	details = allocateDetails();
	//check the mode passed from the user- compression/decompression/other
	EXPECT_EQ(FAILURE, parsing("D:\\short.txt", "comparison"));
}
TEST(parsingArguments, checkIfExistAndRename) {
	details = allocateDetails();
	//Rename output file if a file with that name exists	
	EXPECT_TRUE(0 == strcmp("C:\\Users\\îéøé\\Desktop\\÷åáöé è÷ñè ãéðé\\short-copy.txt", checkAndChangeOutputPath("C:\\Users\\îéøé\\Desktop\\÷åáöé è÷ñè ãéðé\\short.txt", ".txt")));
	//No change to the file name if a file with that name does not already exist
	EXPECT_TRUE(0!= strcmp("C:\\Users\\îéøé\\Desktop\\÷åáöé è÷ñè ãéðé\\dini-copy.txt", checkAndChangeOutputPath("C:\\Users\\îéøé\\Desktop\\÷åáöé è÷ñè ãéðé\\dini.txt", ".txt")));

}

TEST(parsingArguments, checkExtension) {
	details = allocateDetails();
	//check the extension of the source file if it is valid
	EXPECT_EQ(FAILURE, parsing("D:\\short.lzw", "compression"));
	EXPECT_EQ(FAILURE, parsing("D:\\short.txt", "decompression"));
}

TEST(decompress, checkIfEmpty) {
	details = allocateDetails();
	//check if the compressed file is empty
	FILE* fpIn, * fpOut;
	if (openFile("D:\\÷áöé è÷ñè\\empty.bin", &fpIn, "r") &&
		openFile("D:\\÷áöé è÷ñè\\decompressed.txt", &fpOut, "a+")) {
		EXPECT_EQ(FAILURE, decompression(fpIn, fpOut));
	}
}

//TEST(compare, wrapDecompression) {
//	//run the wrapDecompression() function which call the decompression process in comparison
//	details = allocateDetails();
//	FILE* fpCompressed;
//	openFile("D:\\þþCompressionAndDecompression - macro\\CompressionAndDecompression\\CompressionAndDecompression\\text.lzw", &fpCompressed, "rb");
//	EXPECT_EQ(SUCCESS, wrapDecompression(fpCompressed));
//}
//
//TEST(compare, areFileSizesEquals) {
//	//run the wrapDecompression() function which call the decompression process in comparison
//	details = allocateDetails();
//	//open 2 files with the same size
//	FILE* fp1, *fp2;
//	openFile("D:\\þþCompressionAndDecompression - macro\\CompressionAndDecompression\\CompressionAndDecompression\\text.lzw", &fp1, "r");
//	details->inputFileSize = findSize(fp1);
//	openFile("D:\\þþCompressionAndDecompression - macro\CompressionAndDecompression\\CompressionAndDecompression\\text-copy.lzw", &fpOutputDecompression, "r");
//	EXPECT_EQ(SUCCESS, areFileSizesEquals());
//}

TEST(compare, kComparison) {
	//compare between different files
	details = allocateDetails();
	FILE* fp1, * fp2,*fp3;
	unsigned char buffer1[1024];
	unsigned char buffer2[1024];
	openFile("comparison1.txt", &fp1, "r");
	details->inputFileSize = findSize(fp1);
	openFile("comparison2.txt", &fp2, "r");
	EXPECT_EQ(FAILURE, kComparison(fp1, buffer1, buffer2, details->inputFileSize));
	closeFile(fp1);
	//compare between same files
	openFile("comparison1.txt", &fp1, "r");
	openFile("comparison1.tx3", &fp1, "r");
	EXPECT_EQ(SUCCESS, kComparison(fp1, buffer1, buffer2, details->inputFileSize));
}

TEST(compare, wrapCompare) {
	//check the compressed file if it has been compressed well
	details = allocateDetails();
	details->inputFilePath = "D:\\þþCompressionAndDecompression - macro\\CompressionAndDecompression\\CompressionAndDecompression\\text.txt";
	details->outputFilePath = "D:\\þþCompressionAndDecompression - macro\\CompressionAndDecompression\\CompressionAndDecompression\\text.lzw";
	FILE* fp;
	openFile(details->inputFilePath, &fp, "r");
	details->inputFileSize = findSize(fp);
	closeFile(fp);
	//a properly compressed file
	EXPECT_EQ(SUCCESS, wrapCompare());
	//file not compreesed properly
	details->inputFilePath = "D:\\þþCompressionAndDecompression - macro\\CompressionAndDecompression\\CompressionAndDecompression\\comparison1.txt";
	details->outputFilePath = "D:\\þþCompressionAndDecompression - macro\\CompressionAndDecompression\\CompressionAndDecompression\\text.lzw";
	EXPECT_EQ(FAILURE, wrapCompare());


}

TEST(compress, compressionRepeat) {
	details = allocateDetails();
	//compress a file with different languages
	FILE* fpIn, *fpOut;
	openFile("D:\\÷áöé è÷ñè\\differentLanguages.txt", &fpIn, "r");
	openFile("D:\\÷áöé è÷ñè\\differentLanguages.lzw", &fpOut, "ab+");
	EXPECT_EQ(SUCCESS, compression(fpIn, fpOut));

	//compress a very small file 
	openFile("D:\\÷áöé è÷ñè\\small.txt", &fpIn, "r");
	openFile("D:\\÷áöé è÷ñè\\small.lzw", &fpOut, "ab+");
	EXPECT_EQ(SUCCESS, compression(fpIn, fpOut));

	//compress a file whose content repeats itself
	openFile("D:\\÷áöé è÷ñè\\duplicates.txt", &fpIn, "r");
	openFile("D:\\÷áöé è÷ñè\\duplicates.lzw", &fpOut, "ab+");
	EXPECT_EQ(SUCCESS, compression(fpIn, fpOut));


	//compress a file that contains random content
	//compress a file whose content repeats itself
	openFile("D:\\÷áöé è÷ñè\\random.txt", &fpIn, "r");
	openFile("D:\\÷áöé è÷ñè\\random.lzw", &fpOut, "ab+");
	EXPECT_EQ(SUCCESS, compression(fpIn, fpOut));
}







