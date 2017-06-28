#ifndef FRESA_H
#define FRESA_H


#ifdef RASP_OS 
    #define FACTIVE(x) (x)->state == 1 ? 1 : 0
    #define FRESAON(x) digitalWrite((x)->pin, LOW);\
                       (x)->state = 1
                         
    #define FRESAOFF(x) digitalWrite((x)->pin, HIGH);(x)->state = 0
#else 
    #define FACTIVE(x) (x)->state == 1 ? 1 : 0
    #define FRESAON(x) (x)->state = 1
    #define FRESAOFF(x) (x)->state = 0 
#endif


struct fresa_{
    int state;
    int pin;
};

typedef struct fresa_ fresa; 

int alloc_fresa(fresa **f);
int print_fresa(fresa *f);
int read_conf_fresa(fresa *f);
int setup_fresa(fresa *s);


#endif
