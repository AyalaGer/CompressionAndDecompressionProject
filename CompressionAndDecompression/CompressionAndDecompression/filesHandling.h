#pragma once
int closeFile(FILE* fp);
int openFile(char* fPath, FILE** fp, char* mode);
int removeFile(char* fp);
long int findSize(FILE* fp);
int fileSize(FILE* fp);