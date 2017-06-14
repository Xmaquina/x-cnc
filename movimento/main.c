#include <stdlib.h>
#include <stdio.h>
#include "../motor/motor.h"
#include "../sensor/sensor.h"
#include <string.h>
#include "../osmacros.h"
#include "movimento.h"
#include <errno.h>
#ifdef RASP_OS
    #include <wiringPi.h>
#endif


int main(int argv, char *argc[]){
    wiringPiSetup();
    cnc *c;
    alloc_cnc(&c);
    if(c == NULL){
        fprintf(stderr, "It cannot allocated cnc structure because of %s\n",
            strerror(errno));
        return 1;  
    }
     
    return 0;
}
