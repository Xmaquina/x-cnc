#include <stdlib.h>
#include <stdio.h>
#include "../motor/motor.h"
#include "../sensor/sensor.h"
#include <string.h>
#include "../osmacros.h"
#include "movimento.h"
#include <wiringPi.h>
#include <math.h>


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
    //mover_para_ponto_zero(m1);   
    //mover_para_ponto_zero(m);   
    //mover_motor_um_eixo(m1, 10);
    //mover_motor_um_eixo(m, 10);
    //mover_motor_um_eixo(m1, -10);
    //mover_motor_um_eixo(m, -10);
    //move_reta2(m, m1, 2, 2, 8, 7);
    //move_reta2(m, m1, 8, 7, 14, 2);
    move_circulo(m, m1, 2, 3, 4);
    move_circulo(m, m1, 2, 3, 4);
    move_reta2(m, m1, 0, 0, 4, -8 * tan(45*(PI/180)));
    move_reta2(m, m1, 0, 0, 4, 8 * tan(45*(PI/180)));
    //mover_motor_um_eixo(m, 8);
    setdown_motor(m);
    setdown_motor(m1);
    free(m);
    free(m1);
    return 0;
}
