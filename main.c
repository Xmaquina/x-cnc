#include <stdlib.h>
#include <stdio.h>
#include "motor.h"



int conversao(double distance){
    return 0;    
}

int main(){
    motor *m;
    alloc_motor(&m);
    read_conf(m, X_AXIS);
    if(m == NULL){
        printf("You have to allocated it\n");
    }
    read_conf(m, Y_AXIS);
    printf("Testando\n");
    free(m);
    return 0;
}
