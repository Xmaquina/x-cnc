#include <stdlib.h>
#include <stdio.h>
#include "motor.h"
#include <string.h>
#ifdef RASP_OS
    #include <wiringPi.h>
#endif




int main(int argv, char *argc[]){
    #ifdef RASP_OS
    wiringPiSetup();    
    #endif
    motor *m, *m1;
    alloc_motor(&m);
    alloc_motor(&m1);
    read_conf(m, X_AXIS);
    read_conf(m1, Y_AXIS);
    if(m == NULL){
        printf("You have to allocated it\n");
    }
    int time = 0;
    setup_motor(m);
    set_sixteenth_step(m);
    printf("Esse teste é feito para verificar se a direcaco esta mudando:\n");
    printf("Primeiro movendo pra frente por 200 ms.\n");
    FORWARD(m);
    while(time < 200){
        MOVE(m);
        time += 1;
    }
    #ifdef RASP_OS
    delay(2000);
    #endif
    printf("Depois movendo para trás por 200 ms.\n");
    time = 0;
    BACKWARD(m);
    while(time < 200){
        MOVE(m);
        time += 1;
    }
    setdown_motor(m);
    free(m);
    free(m1);
    return 0;
}
