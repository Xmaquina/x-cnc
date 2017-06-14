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
    m = get_motor(x_axis);
    m1 = get_motor(y_axis);
    m2 = get_motor(z_axis);
    if(m == NULL){
        printf("You have to allocated it\n");
    }
    printf("Pit step: %d\n", m->pin_step);
    //printf("Pit step: %d\n", m1->pin_step);
    setup_motor(m);
    setup_motor(m1);
    setup_motor(m2);
    
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
       //delayMicroseconds(50);
       //delay(1000);   
        
    }
    setdown_motor(m);
    setdown_motor(m1);
    free(m);
    free(m1);
    //free(m1);
    return 0;
}
