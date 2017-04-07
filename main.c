#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include "motor.h"



int conversao(double distance){
    
}

int main(){
    motor *m;
    wiringPiSetupGpio();
    pinMode(17, OUTPUT);
    digitalWrite(23, HIGH);
    read_conf(m, X_AXIS);
    printf("Testando");
    return 0;
}
