#include "motor.h"
#include "xcncmacros.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<wiringPi.h>
#include <errno.h>

int alloc_motor(motor **m){
    *m = (motor *)malloc(sizeof(motor));
    if(*m == NULL){
        fprintf(stderr, "It cannot alloccate motor structure because %sn",
                strerror(errno)); 
        return 1;
    }
    return 0;   
}
char * type_axis(motor *m){
    if(m->axis == X_AXIS){
        return CX_AXIS;
    }else if(m->axis == Y_AXIS){
        return CY_AXIS;
    }else if(m->axis == Z_AXIS){
        return CZ_AXIS;
    }
    return "";
}

char * type_axis_c(motor_axis m){
    if(m == X_AXIS){
        return CX_AXIS;
    }else if(m == Y_AXIS){
        return CY_AXIS;
    }else if(m == Z_AXIS){
        return CZ_AXIS;
    }
    return "";
}

char * motor_file_name(motor *m){
//printf("Por acaso o erro esta na funcao motor_file_name\n");
    char * f = "conf/stepper-motor-";
    char * r = malloc(sizeof(char) * 120);
//printf("Por acaso o erro esta na funcao motor_file_name linha 16-18\n");
    strcpy(r,f);
//printf("Por acaso o erro esta na funcao motor_file_name linha 20\n");
    strcat(r, type_axis(m));
//printf("Por acaso o erro esta na funcao motor_file_name linha 22\n");
//printf("Motor file name: %s\n", r);
    return r;
}
int motor_file_exists(motor *m){
    FILE *file;
    char *fname = motor_file_name(m);
//printf("Motor file name 2: %s\n", fname);
    file = fopen(fname, "r");
    if(file == NULL){
        //printf("Oh dear, something went wrong with read()! %s\n", strerror(errno));
    }
    if ((file = fopen(fname, "r"))){
        fclose(file);
        return 1;
    }
    return 0;
}

int print_motor(motor *m){
    printf("Angle: %lf\n", m->step);
    return 1;
}

int read_conf(motor *m, int motor){
    if(m == NULL){ exit(EXIT_FAILURE); };
    m->axis = motor;
    FILE *fp;
    if(motor_file_exists(m)){
        fp = fopen(motor_file_name(m), "r");
    }else{
        fp = fopen("conf/stepper-motor", "r");
    }
    char buffer[255];
    double angle = 0;
    fscanf(fp, "%s = %lf", buffer, &angle);
    if(strcmp(buffer, "angle") == 0){
        m->step = angle;
    }
    print_motor(m);
    fclose(fp); 
    
   return 0; 

}


int move_motor(motor *m){
#ifdef RASP_OS 
    pinMode(17, OUTPUT);
#endif
    return 0;
    
}
