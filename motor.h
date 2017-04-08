#ifndef MOTOR_H
#define MOTOR_H

#define X_AXIS 1
#define Y_AXIS 2
#define Z_AXIS 3
#define CX_AXIS "X_AXIS"
#define CY_AXIS "Y_AXIS"
#define CZ_AXIS "Z_AXIS"

enum motor_axis_{
    x_axis = X_AXIS,
    y_axis = Y_AXIS,
    z_axis = Z_AXIS
};


typedef enum motor_axis_ motor_axis;

struct motor_{
    double step;
    motor_axis axis;
 
};

typedef struct motor_ motor; 

int read_conf(motor * m, int motor);
int move_motor(motor *m);
char * type_axis(motor *m);

#endif
