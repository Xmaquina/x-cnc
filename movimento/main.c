#include <stdlib.h>
#include <stdio.h>
#include "../motor/motor.h"
#include "../sensor/sensor.h"
#include <string.h>
#include "../osmacros.h"
#include "movimento.h"
#ifdef RASP_OS
    #include <wiringPi.h>
#endif


int main(int argv, char *argc[]){
    wiringPiSetup();
    motor *m, *m1;
    alloc_motor(&m);
    alloc_motor(&m1);
    read_conf(m, X_AXIS);
    read_conf(m1, Y_AXIS);
    if(m == NULL){
        printf("You have to allocated it\n");
    }
    setup_motor(m);
    setup_motor(m1);
    mover_para_ponto_zero(m1);   
    mover_para_ponto_zero(m);   
    setdown_motor(m);
    setdown_motor(m1);
    free(m);
    free(m1);
    return 0;
}
