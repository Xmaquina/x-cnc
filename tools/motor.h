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
#define MS1 "ms1" 
#define MS2 "ms2" 
#define MS3 "ms3" 
#define SET_STEP "set_step" 
#define DRIVER "driver" 
#include "../osmacros.h"
#include "sensor.h"

#ifdef RASP_OS 
        #define MOVE(x) \
                        if((x)->driver == 2){ \
                            digitalWrite((x)->pin_step,HIGH); \
                            digitalWrite((x)->pin_step,LOW); \
                        }else{ \
                            digitalWrite((x)->pin_step,LOW); \
                            digitalWrite((x)->pin_step,HIGH); }
    #define STOP(x) digitalWrite((x)->pin_step,HIGH) 
    #define FORWARD(x) digitalWrite((x)->pin_direction, HIGH)
    #define BACKWARD(x) digitalWrite((x)->pin_direction, LOW)
#else
    #define MOVE(x) printf("movimento\n") 
    #define STOP(x)  printf("stop\n") 
    #define FORWARD(x) printf("pra frente\n") 
    #define BACKWARD(x) printf("pra tras\n") 

#endif
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
    int pin_ms1;
    int pin_ms2;
    int pin_ms3;
    int set_step;
    sensor *s;
    int driver;
};

typedef struct motor_ motor; 

int alloc_motor(motor **m);
int read_conf(motor * m, int motor);
int print_motor(motor *m);
char * type_axis(motor *m);
char * type_axis_c(motor_axis m);
int set_sixteenth_step(motor *m);
int set_eighth_step(motor *m);
int set_quarter_step(motor *m);
int set_half_step(motor *m);
int set_full_step(motor *m);
int setup_step(motor *m, int step);
int setup_motor(motor *m);
int setdown_motor(motor *m);
int move_motor(motor *m, int direction, int voltas);
void bresenham1(motor *mx, motor *my, int x1, int y1, int x2, int y2);
motor* get_motor(motor_axis axis);
#endif
