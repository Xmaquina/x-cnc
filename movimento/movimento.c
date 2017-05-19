#include "movimento.h"
#include "../motor/motor.h"
#include "../sensor/sensor.h"
#include "../xcncmacros.h"
#include "../osmacros.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../token/token.h"

#ifdef RASP_OS 
    #include<wiringPi.h>
#endif
#include <errno.h>

int mover_para_ponto_zero(motor *m){
    sensor *s;
    alloc_sensor(&s);
    if(m->axis == x_axis){
       read_conf_sensor(s, SX_AXIS);    
    }
    if(m->axis == y_axis){
       read_conf_sensor(s, SX_AXIS);    
       FORWARD(m);
    }
    setup_step(m, 3);
    while(1){
        SREAD(s);
        printf("active: %d\n", SACTIVE(s));
        if(SACTIVE(s)){
          break;
        }
        delay(2);
        MOVE(m);
    }
    setup_step(m, m->set_step);
    return 1;
}

