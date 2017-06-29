#ifndef MOVIMENTO_H
#define MOVIMENTO_H

#define PI 3.14159265
#include "../tools/motor.h"
#include "../tools/fresa.h"
#include "../tools/laser.h"
#include "../tools/sensor.h"
#include "../gcode/gcode.h"
#include "../osmacros.h"
#include "../tools/cnc.h"

struct ponto_{
    double x;
    double y;
    double z;
};



typedef struct ponto_ ponto;

int mover_para_ponto_zero(motor *m);
int mover_zero(motor *xm, motor *ym, sensor *sx, sensor *sy);
int move_reta(motor *m, motor *m1, double x, double y, double x1, double y1);
int mover_motor_um_eixo(motor *m, double mm);
int move_reta2(motor *m, motor *m1, double x, double y, double x1, double y1);
int move_circulo(motor *m, motor *m1, double x, double y, double r);
int move_circulo_eixoy(motor *m, motor *m1, double x, double y, double r);
int mover_zero_cnc(cnc *c);
int executar(cnc *c, gcommand *g,gcommand *bg, ponto *p);
#endif
