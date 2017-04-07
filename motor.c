#include "motor.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int alloc_motor(motor **m){
    *m = (motor *)malloc(sizeof(motor));
    if(*m == NULL){
printf("It cannot allocate motor");
        return 1;
    }
    return 0;   
}
char * motor_file_name(int motor){
printf("Por acaso o erro esta na funcao motor_file_name\n");
    char * f = "./conf/stepper-motor-";
    char r[120];
    char n[2];
    n[0] = motor + 60;
printf("Por acaso o erro esta na funcao motor_file_name linha 16-18\n");
    strcat(r,f);
printf("Por acaso o erro esta na funcao motor_file_name linha 20\n");
    strcat(r, n);
printf("Por acaso o erro esta na funcao motor_file_name linha 22\n");
printf("Motor file name: %s\n", r);
    return r;
}
int motor_file_exists(int motor){
    FILE *file;
    char *fname = motor_file_name(motor);
    if ((file = fopen(fname, "r"))){
        fclose(file);
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
    if(motor_file_exists(motor)){
        fp = fopen(motor_file_name(motor), "r");
    }else{
        fp = fopen("conf/stepper-motor", "r");
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
    
}
