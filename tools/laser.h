#ifndef LASER_H
#define LASER_H


#ifdef RASP_OS 
    #define LACTIVE(x) (x)->state == 1 ? 1 : 0
    #define LASEROFF(x) digitalWrite((x)->pin, LOW);\
                       (x)->state = 0
    #define LASERON(x) digitalWrite((x)->pin, HIGH);\
                       (x)->state = 1
#else 
    #define LACTIVE(x) (x)->state == 1 ? 1 : 0
    #define LASERON(x) (x)->state = 1; printf("deu\n")
    #define LASEROFF(x) (x)->state = 0 
#endif


struct laser_{
    int state;
    int pin;
};

typedef struct laser_ laser; 

int alloc_laser(laser **l);
int print_laser(laser *l);
int read_conf_laser(laser *l);
int setup_laser(laser *l);


#endif
