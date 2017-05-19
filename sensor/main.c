#include <stdlib.h>
#include <stdio.h>
#include "sensor.h"
#include "../token/token.h"
#include <string.h>
#ifdef RASP_OS
    #include <wiringPi.h>
#endif


int main(int argv, char *argc[]){
    sensor *s;
    alloc_sensor(&s);
    read_conf_sensor(s, SX_AXIS);
    printf("Deu certo\n");
    free(s);
    return 0;
}
