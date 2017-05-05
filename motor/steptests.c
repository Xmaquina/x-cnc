#include <stdlib.h>
#include <stdio.h>
#include "motor.h"
#include <string.h>
#include <wiringPi.h>



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
    setup_motor(m);
    printf("Sixteenth\n");
    set_sixteenth_step(m);
    delay(4000);
    printf("Eighth\n");
    set_eighth_step(m);
    delay(4000);
    printf("Quarter\n");
    set_quarter_step(m);
    delay(4000);
    printf("Half\n");
    set_half_step(m);
    delay(4000);
    printf("Full\n");
    set_full_step(m);
    delay(4000);
    setdown_motor(m);
    free(m);
    free(m1);
    return 0;
}
