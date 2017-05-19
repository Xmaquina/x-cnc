#include <stdlib.h>
#include <stdio.h>
#include "sensor.h"
#include "../token/token.h"
#include <string.h>
#ifdef RASP_OS
    #include <wiringPi.h>
#endif

#include <wiringPi.h>

int main(int argv, char *argc[]){
    sensor *s;
    alloc_sensor(&s);
    read_conf_sensor(s, SX_AXIS);
    setup_sensor(s);
    wiringPiSetup();
    while(1){
        SREAD(s);
        //int d = digitalRead(s->pin);
printf("The state %d\n", s->state);
        delay(1);
    }
    printf("Deu certo\n");
    free(s);
    return 0;
}
