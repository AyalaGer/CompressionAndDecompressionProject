#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "detailsStruct.h"
#include <string.h>
extern struct Details* details;

#define LOG 1
#if LOG
#define LOG_INFO(func,msg) fprintf(details->fpLogFile, "%s, %s, %s\n", calcTime(), func, msg);
#define CREATE_LOG_FILE details->fpLogFile = fopen("log.csv", "a+"); fprintf(details->fpLogFile, "Time, Function, Message\n"); 
#define CLOSE_LOG int x=fclose(details->fpLogFile);
#else 
#define MACRO_LOG(func,msg) 
#define CREATE_LOG_FILE 
#define CLOSE_LOG
#endif