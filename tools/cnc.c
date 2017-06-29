#include "cnc.h"
#include "motor.h"
#include "laser.h"
#include "fresa.h"
#include "sensor.h"
#include "../xcncmacros.h"
#include "../osmacros.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "../token/token.h"

#ifdef RASP_OS 
    #include<wiringPi.h>
#endif
#include<errno.h>

int alloc_cnc(cnc **c){
    *c = (cnc *)malloc(sizeof(cnc));
    if(*c == NULL){
        fprintf(stderr, "It cannot alloccate motor structure because %s\n",
                strerror(errno));    
        return 1;
    }
    return 0;   
}

int read_cnc(cnc *c){
    alloc_laser(&c->l);
    alloc_fresa(&c->f);
    read_conf_fresa(c->f);
    read_conf_laser(c->l);
    c->xm = get_motor(x_axis);
    c->ym = get_motor(y_axis);
    c->zm = get_motor(z_axis);
    return 1;
}

int isLaser(cnc *c){
    if(c->type_of_work == LASER){
        return 1;
    }
    return 0;
}

int isFresa(cnc *c){
    if(c->type_of_work == FRESA){
        return 1;
    }
    return 0;
}

int set_work(cnc *c, int op){
    if(op == FRESA){
        c->type_of_work = op;
    }else if(op == LASER){
        c->type_of_work = op;
    }else{
        c->type_of_work = LASER;
        //TODO
        //print it to a log file
        printf("Opcao de trabalho errada\n");
    }
    return 1;
}

