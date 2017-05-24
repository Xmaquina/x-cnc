#ifndef MOVIMENTO_H
#define MOVIMENTO_H

#include "../motor/motor.h"
#include "../sensor/sensor.h"
#include "../osmacros.h"

int mover_para_ponto_zero(motor *m);
int mover_zero(motor *xm, motor *ym, sensor *sx, sensor *sy);
int move_reta(motor *m, motor *m1, double x, double y, double x1, double y1);

#endif
