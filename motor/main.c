#include <stdlib.h>
#include <stdio.h>
#include "motor.h"
#include <string.h>
#include <wiringPi.h>

#define MOVE(x) digitalWrite(x->step,HIGH) 



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
    printf("Pit step: %d\n", m->pin_step);
    printf("Pit step: %d\n", m1->pin_step);
    pinMode(m->pin_step, OUTPUT);
    pinMode(m1->pin_step, OUTPUT);
    for(int i = 0; i < 10; i++){
        printf("Pinos sendo ativado\n");
        digitalWrite(m->pin_step, HIGH);
        digitalWrite(m1->pin_step, LOW);
        delay(700);
        printf("Pinos sendo desativado\n");
        digitalWrite(m->pin_step, LOW);
        digitalWrite(m1->pin_step, HIGH);
        //MOVE(m1);
        delay(700);
    }
    free(m);
    free(m1);
    return 0;
}
