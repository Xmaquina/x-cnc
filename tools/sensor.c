#include "sensor.h"
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

int alloc_sensor(sensor **s){
    *s = (sensor *)malloc(sizeof(sensor));
    if(*s == NULL){
        fprintf(stderr, "It cannot alloccate motor structure because %sn",
                strerror(errno)); 
        return 1;
    }
    return 0;   
}

int setup_sensor(sensor *s){
    #ifdef RASP_OS 
        pinMode(s->pin, INPUT);
    #endif
    return 0;

}
char * type_saxis(sensor *s){
    if(s->axis == SX_AXIS){
        return SCX_AXIS;
    }else if(s->axis == SY_AXIS){
        return SCY_AXIS;
    }else if(s->axis == SZ_AXIS){
        return SCZ_AXIS;
    }
    return "";
}


int print_sensor(sensor *s){
    printf("pin: %d\n", s->pin);
    return 1;
}

int read_conf_sensor(sensor *s, int sensor){
    if(s == NULL){ exit(EXIT_FAILURE); };
    s->axis = sensor;
    FILE *fp;
    char *filename = file_name(file_name(CONFDIR,"sensor-"), type_saxis(s));
printf("filename %s\n", filename);
    if(file_exists(filename)){
        fp = fopen(filename, "r");
    }else{
        fp = fopen("conf/sensor", "r");
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
        s->pin = value;
    } 
    print_sensor(s);
    fclose(fp); 
    
   return 0; 

}

int isAcative(sensor *s){
    if(s->state == 0) return 1;
    return 0;
}


