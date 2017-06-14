#ifndef MOVIMENTO_H
#define MOVIMENTO_H

#define PI 3.14159265
#include "../motor/motor.h"
#include "../sensor/sensor.h"
#include "../osmacros.h"

struct ponto_{
    double x;
    double y;
    double z;
};

struct cnc_{
    motor *xm;
    motor *ym;
    motor *zm;
};

typedef struct ponto_ ponto;
typedef struct cnc_ cnc;

int alloc_cnc(cnc **c);
int read_cnc(cnc *c);
int mover_para_ponto_zero(motor *m);
int mover_zero(motor *xm, motor *ym, sensor *sx, sensor *sy);
int move_reta(motor *m, motor *m1, double x, double y, double x1, double y1);
int mover_motor_um_eixo(motor *m, double mm);
int move_reta2(motor *m, motor *m1, double x, double y, double x1, double y1);
int move_circulo(motor *m, motor *m1, double x, double y, double r);
int move_circulo_eixoy(motor *m, motor *m1, double x, double y, double r);
#endif
