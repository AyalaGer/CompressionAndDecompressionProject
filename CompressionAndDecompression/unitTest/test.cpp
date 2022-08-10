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

TEST(parsingArguments, checKLimitFileSize) {
	details = allocateDetails();
	//check the limit of file size
	char* path= "C:\\Users\\מירי\\Downloads\\omlyTest.txt", * mode="compression";
	EXPECT_EQ(0, parsing(path, mode));
	//check the mode passed from the user- compression/decompression/other
	EXPECT_EQ(0, parsing("D:\\short.txt", "comparison"));
	//Rename output file if a file with that name exists	
	EXPECT_TRUE(0==strcmp("C:\\Users\\מירי\\Desktop\\קובצי טקסט דיני\\short-copy.txt", checkAndChangeOutputPath("C:\\Users\\מירי\\Desktop\\קובצי טקסט דיני\\short.txt",".txt")));

}