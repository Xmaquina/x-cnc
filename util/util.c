#include "util.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "../osmacros.h"

int file_exists(char *name){
    FILE *file;
    if((file = fopen(name, "r"))){
        fclose(file);
        return 1;
    }
    return 0;

}

FILE * open_file(char* file){
    FILE *fp;
    char *filename = file_name(CONFDIR,file);
    printf("filename %s\n", filename);
    if(file_exists(filename)){
        fp = fopen(filename, "r");
    }else{
        exit(EXIT_FAILURE); 
    }
    if(fp == NULL){
        fprintf (stderr, "Couldn't open file conf/fresa; %s\n",
                 strerror (errno));
        exit (EXIT_FAILURE);
    }
    return fp;
}

char* file_name(char *pre, char *suf){
    if(pre == NULL || suf == NULL) return NULL;
    char *r = malloc(sizeof(char) * (strlen(pre) + strlen(suf) + 2));
    strcpy(r, pre);
    strcat(r,suf);
    return r;
}

