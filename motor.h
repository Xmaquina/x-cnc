#ifndef MOTOR_H
#define MOTOR_H

enum motor_axis{
    X_AXIS,
    Y_AXIS,
    Z_AXIS
};

struct motor_{
    double step;
    int motor_axis;

};

typedef struct motor_ motor; 

int read_conf(motor * m, int motor);

#endif
