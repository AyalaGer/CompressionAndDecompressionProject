#include "pch.h"
#include "../CompressionAndDecompression/filesHandling.h"
#include "../CompressionAndDecompression/filesHandling.c"
#include "../CompressionAndDecompression/detailsStruct.h"
#include "../CompressionAndDecompression/detailsStruct.c"
TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
} 
//Open files
TEST(FileHandling, OpenFile) {
	FILE* fp;
	char* path="txt.txt";
	char* path1 = "txt1.txt";
	//Open a valid file.
	EXPECT_EQ(1,openFile(path,&fp,"a+"));
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
}
