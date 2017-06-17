#include "laser.h"
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
int alloc_laser(laser **l){
    *l = (laser *)malloc(sizeof(laser));
    if(*l == NULL){
        fprintf(stderr, "It cannot alloccate motor structure because %s\n",
                strerror(errno)); 
        return 1;
    }
    return 0;   
}

int print_laser(laser *l){
    printf("Laser\n");
    printf("pin: %d\n", l->pin);
    return 1;
}

int read_conf_laser(laser *l){
    if(l == NULL){ exit(EXIT_FAILURE); };
    FILE *fp;
    char *filename = file_name(CONFDIR,"laser");
printf("filename %s\n", filename);
    if(file_exists(filename)){
        fp = fopen(filename, "r");
    }else{
        exit(EXIT_FAILURE); 
    }
    if(fp == NULL){
        fprintf (stderr, "Couldn't open file conf/sensor; %s\n",
                 strerror (errno));
        exit (EXIT_FAILURE);
    }
    char buffer[255];
    int value = 0;
    fscanf(fp, "%s = %d", buffer, &value);
    if(strcmp(buffer, "pin") == 0){
        l->pin = value;
    } 
    print_laser(l);
    fclose(fp); 
    
   return 0;
}

int setup_laser(laser *l){
    #ifdef RASP_OS 
        pinMode(l->pin, OUTPUT);
    #endif
    return 0;
}
