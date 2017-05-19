#ifndef SENSOR_H
#define SENSOR_H

#define SX_AXIS 1
#define SY_AXIS 2
#define SZ_AXIS 3
#define SCX_AXIS "X_AXIS"
#define SCY_AXIS "Y_AXIS"
#define SCZ_AXIS "Z_AXIS"
#ifdef RASP_OS 
    #define SACTIVE(x) (x)->state == 0 ? 1 : 0
    #define SREAD(x) (x)->state = digitalRead((x)->pin) 
#endif

//const char *properties[4] = {ANGLE, DIRECTION, STEP, LIMIT};

enum sensor_axis_{
    sx_axis = SX_AXIS,
    sy_axis = SY_AXIS,
    sz_axis = SZ_AXIS
};


typedef enum sensor_axis_ sensor_axis;

struct sensor_{
    int state;
    sensor_axis axis;
    int pin;
 
};

typedef struct sensor_ sensor; 

int alloc_sensor(sensor **s);
char * type_saxis(sensor *s);
int print_sensor(sensor *s);
int read_conf_sensor(sensor *s, int sensor);
int setup_sensor(sensor *s);


#endif
