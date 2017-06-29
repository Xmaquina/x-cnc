#include <stdlib.h>
#include <stdio.h>
#include "../sensor.h"
#include <string.h>
#ifdef RASP_OS
    #include <wiringPi.h>
#endif


int main(int argv, char *argc[]){
    sensor *s;
    alloc_sensor(&s);
    read_conf_sensor(s, SX_AXIS);
    setup_sensor(s);
    #ifdef RASP_OS
        wiringPiSetup();
    #endif
    while(1){
        SREAD(s);
        //int d = digitalRead(s->pin);
printf("The state %d\n", s->state);
        #ifdef RASP_OS
            delay(DELAY_TIME);
        #endif
    }
    printf("Deu certo\n");
    free(s);
    return 0;
}
