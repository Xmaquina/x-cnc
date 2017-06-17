#include "fresa.h"
#include "../xcncmacros.h"
#include "../osmacros.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../util/util.h"
#ifdef RASP_OS 
    #include<wiringPi.h>
#endif
#include <errno.h>
int alloc_fresa(fresa **f){
    *f = (fresa *)malloc(sizeof(fresa));
    if(*f == NULL){
        fprintf(stderr, "It cannot alloccate motor structure because %s\n",
                strerror(errno)); 
        return 1;
    }
    return 0;   
}

int print_fresa(fresa *f){
    printf("Fresa\n");
    printf("pin: %d\n", f->pin);
    return 1;
}

int read_conf_fresa(fresa *f){
    if(f == NULL){ exit(EXIT_FAILURE); };
    FILE *fp;
    char *filename = file_name(CONFDIR,"fresa");
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
    char buffer[255];
    int value = 0;
    fscanf(fp, "%s = %d", buffer, &value);
    if(strcmp(buffer, "pin") == 0){
        f->pin = value;
    } 
    print_fresa(f);
    fclose(fp); 
    
   return 0;
}

int setup_fresa(fresa *f){
    #ifdef RASP_OS 
        pinMode(f->pin, OUTPUT);
    #endif
    return 0;
}
