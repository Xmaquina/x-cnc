#include <stdlib.h>
#include <stdio.h>
#include "laser.h"
#include "../token/token.h"
#include <string.h>
#ifdef RASP_OS
    #include <wiringPi.h>
#endif


int main(int argv, char *argc[]){
    if(argv < 2){
        printf("Voce precisa passar a quantidade de voltas que a laser estara \
                ativa\n");
        exit(EXIT_FAILURE);
    }
    int qtde = atoi(argc[1]);
printf("A qtde: %d\n", qtde);
    laser *l;
    alloc_laser(&l);
    read_conf_laser(l);
    LASERON(l);
    for(int i = 0; i < qtde; i++){
        printf("nada\n");
    } 
    LASEROFF(l);
    printf("Deu certo\n");
    return 0;
}
