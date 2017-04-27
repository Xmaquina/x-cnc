#ifndef MOTOR_H
#define MOTOR_H

#define X_AXIS 1
#define Y_AXIS 2
#define Z_AXIS 3
#define CX_AXIS "X_AXIS"
#define CY_AXIS "Y_AXIS"
#define CZ_AXIS "Z_AXIS"
#define ANGLE "angle"
#define DIRECTION "direction"
#define STEP "step"
#define LIMIT "limit" 

//const char *properties[4] = {ANGLE, DIRECTION, STEP, LIMIT};

enum motor_axis_{
    x_axis = X_AXIS,
    y_axis = Y_AXIS,
    z_axis = Z_AXIS
};


typedef enum motor_axis_ motor_axis;

struct motor_{
    double step;
    motor_axis axis;
    int pin_direction;
    int pin_step;
    int pin_limit;
    
 
};

typedef struct motor_ motor; 

int alloc_motor(motor **m);
int read_conf(motor * m, int motor);
int move_motor(motor *m);
char * type_axis(motor *m);
char * type_axis_c(motor_axis m);

#endif
