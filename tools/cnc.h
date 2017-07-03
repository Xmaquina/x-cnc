#ifndef CNC_H
#define CNC_H

#define PI 3.14159265
#include "motor.h"
#include "fresa.h"
#include "laser.h"
#include "sensor.h"
#include "../osmacros.h"

#define FRESA 1
#define LASER 2
 
struct cnc_{
    motor *xm;
    motor *ym;
    motor *zm;
    laser *l;
    fresa *f;
    int type_of_work;
};

typedef struct cnc_ cnc;

int alloc_cnc(cnc **c);
int read_cnc(cnc *c);
int set_work(cnc *c, int op);
int isLaser(cnc *c);
int isFresa(cnc *c);
int setdown_cnc(cnc *c);
#endif
