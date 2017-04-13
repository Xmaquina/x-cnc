#include "motor.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<wiringPi.h>
#include <errno.h>

int alloc_motor(motor **m){
    *m = (motor *)malloc(sizeof(motor));
    if(*m == NULL){
printf("It cannot allocate motor");
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
printf("Por acaso o erro esta na funcao motor_file_name\n");
    char * f = "./conf/stepper-motor-";
    char r[120];
    char n[2];
    sprintf(n,"%d",m->axis); 
printf("Por acaso o erro esta na funcao motor_file_name linha 16-18\n");
    strcat(r,f);
printf("Por acaso o erro esta na funcao motor_file_name linha 20\n");
    strcat(r, type_axis(m));
printf("Por acaso o erro esta na funcao motor_file_name linha 22\n");
printf("Motor file name: %s\n", r);
    return r;
}
int motor_file_exists(motor *m){
    FILE *file;
    char *fname = motor_file_name(m);
printf("Motor file name 2: %s\n", fname);
    file = fopen(fname, "r");
    if(file == NULL){
    printf("Oh dear, something went wrong with read()! %s\n", strerror(errno));
    }
    if ((file = fopen(fname, "r"))){
        fclose(file);
printf("Retornou 1\n"); 
        return 1;
    }
    return 0;
}

int read_conf(motor *m, int motor){
printf("Starting read conf\n");
    if(alloc_motor(&m)){ exit(1); };
printf("Allocated motor\n");
    if(m == NULL){
printf("Vai tomar no cu\n"); 
    }
    m->axis = motor;
printf("Onde esta o erro? aqui\n"); 
    FILE *fp;
    if(motor_file_exists(m)){
        fp = fopen(motor_file_name(m), "r");
    }else{
printf("Retorno errado\n"); 
        fp = fopen("conf/stepper-motor-X_AXIS", "r");
    }
    char buffer[255];
    double angle = 0;
    fscanf(fp, "%s = %lf", buffer, &angle);
printf("O que foi lido do arquivo:\n");
printf("%s=%lf\n", buffer, angle);
    if(strcmp(buffer, "angle") == 0){
        m->step = angle;
    }

    fclose(fp); 
    
   return 0; 

}



int move_motor(motor *m){
    pinMode(17, OUTPUT);
    return 0;
    
}
