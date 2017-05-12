#include <stdlib.h>
#include <stdio.h>
#include "motor.h"
#include <string.h>
#ifdef RASP_OS
    #include <wiringPi.h>
#endif


int main(int argv, char *argc[]){
    int direcao = atoi(argc[1]);
printf("A direcao %d\n", direcao);
    int qtde = atoi(argc[2]);
printf("A qtde %d\n", qtde);
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
    printf("Pit step: %d\n", m->pin_step);
    //printf("Pit step: %d\n", m1->pin_step);
    setup_motor(m);
    //set_eighth_step(m);
     /*
    for(int i = 0; i < 10; i++){
        printf("Pinos sendo ativado\n");
        MOVE(m);
        STOP(m1);
        delay(700);
        printf("Pinos sendo desativado\n");
        STOP(m);
        MOVE(m1);
        delay(700);
    }
    //STOP(m1);
    STOP(m);
    */
    //delay(5000); 
    if(direcao == 1){
        BACKWARD(m);
        BACKWARD(m1);
    }else{
        FORWARD(m);
        FORWARD(m1);
    }
    for(int i = 0; i < qtde; i++){ 
        //printf("movendo\n");
        MOVE(m);
        delay(1);
        MOVE(m1);
        //FORWARD(m);
        delay(1);
        //printf("Indo pra tras\n");
        //BACKWARD(m);
        //printf("Parado:\n");
        //delay(2);
    }
    setdown_motor(m);
    setdown_motor(m1);
    free(m);
    free(m1);
    return 0;
}
