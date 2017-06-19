#include <stdlib.h>
#include <stdio.h>
#include "../motor/motor.h"
#include "../sensor/sensor.h"
#include <string.h>
#include "../osmacros.h"
#include "movimento.h"
#include "cnc.h"
#include <errno.h>
#ifdef RASP_OS
    #include <wiringPi.h>
#endif


int main(int argv, char *argc[]){
    #ifdef RASP_OS
    wiringPiSetup();
    #endif
    cnc *c;
    alloc_cnc(&c);
    read_cnc(c);
    if(c == NULL){
        fprintf(stderr, "It cannot allocated cnc structure because of %s\n",
            strerror(errno));
        return 1;  
    }
    mover_zero_cnc(c);     
    return 0;
}
