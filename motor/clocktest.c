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
    pinMode(1, PWM_OUTPUT);
    pwmSetClock(1920);
    pwmSetRange (400) ;
    pwmWrite (1, 20);
    delay(100);
    pinMode(1, OUTPUT);
    digitalWrite(1,LOW);
    printf("Deu certo\n");
    return 0;
}
