#include <stdlib.h>
#include <stdio.h>
#include "motor.h"
#include <string.h>





int main(int argv, char *argc[]){
        
    motor *m;
    alloc_motor(&m);
    read_conf(m, X_AXIS);
    if(m == NULL){
        printf("You have to allocated it\n");
    }
    free(m);
    return 0;
}
