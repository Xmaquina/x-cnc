#ifndef UTIL_H
#define UTIL_H
#include<stdio.h>
FILE * open_file(char* file);
int file_exists(char *name);
char* file_name(char *pre, char *suf);
#endif
