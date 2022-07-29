#define _CRT_SECURE_NO_WARNINGS
#include "compress.h"
#include "decompress.h"
#include "compare.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int compare(FILE* fpSource, FILE* fpOutput)
{
    //Print to the logging file
//check if they have equal size??
    FILE* tempOutput = fopen("tempDecompress.txt", "a");
    char* DecompressionOutputPath = decompression(fpOutput, tempOutput);
    FILE* fpDecompressionOutput = fopen(DecompressionOutputPath, "r");
    char ch1 = getc(fpSource);
    char ch2 = getc(fpDecompressionOutput);

    // pos keeps track of position of errors
    // line keeps track of error line
    int pos = 0, line = 1;
    while (ch1 != EOF && ch2 != EOF)
    {
        pos++;
        if (ch1 == '\n' && ch2 == '\n')
        {
            line++;
            pos = 0;
        }
        if (ch1 != ch2)
        {
            //print to logging:  ("Line Number : %d \tError"
            //    " Position : %d \n", line, pos);
            return 0;
        }
        ch1 = getc(fpSource);
        ch2 = getc(fpDecompressionOutput);
    }
    //print to logging file
    return 1;

}