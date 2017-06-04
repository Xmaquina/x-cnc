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
    int direcao2 = atoi(argc[3]);
printf("A direcao2 %d\n", direcao);
    int direcao3 = atoi(argc[4]);
printf("A direcao3 %d\n", direcao);
    int mot = atoi(argc[5]);
printf("Motes %d\n", mot);
    #ifdef RASP_OS
    wiringPiSetup();
    #endif    
    motor *m, *m1, *m2;
    alloc_motor(&m);
    alloc_motor(&m1);
    alloc_motor(&m2);
    read_conf(m, X_AXIS);
    read_conf(m1, Y_AXIS);
    read_conf(m2, Z_AXIS);
    if(m == NULL){
        printf("You have to allocated it\n");
    }
    printf("Pit step: %d\n", m->pin_step);
    //printf("Pit step: %d\n", m1->pin_step);
    setup_motor(m);
    setup_motor(m1);
    setup_motor(m2);
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
    }else{
        FORWARD(m);
    }
    if(direcao2 == 1){
        BACKWARD(m1);
    }else{
        FORWARD(m1);
    }
    if(direcao3 == 1){
        BACKWARD(m2);
    }else{
        FORWARD(m2);
    }
    for(int i = 0; i < qtde; i++){ 
        //printf("movendo\n");
        if(mot == 1){
            MOVE(m);
        }else if(mot == 2){
            MOVE(m1);
        }else if(mot == 3){
            MOVE(m);
            MOVE(m1);
        }else if(mot == 4){
            MOVE(m);
            MOVE(m1);
            MOVE(m2);
        }else if(mot == 5){
            MOVE(m2);
        }
        delay(1);
    }
    setdown_motor(m);
    setdown_motor(m1);
    free(m);
    free(m1);
    //free(m1);
    return 0;
}
