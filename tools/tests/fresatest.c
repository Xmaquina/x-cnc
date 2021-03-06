#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../fresa.h"
#include <string.h>
#include "../../osmacros.h"
#ifdef RASP_OS
    #include <wiringPi.h>
#endif


int main(int argv, char *argc[]){
    if(argv < 2){
        printf("Voce precisa passar a quantidade de voltas que a fresa estara \
                ativa\n");
        exit(EXIT_FAILURE);
    }
    int qtde = atoi(argc[1]);
printf("A qtde: %d\n", qtde);
    fresa *f;
    alloc_fresa(&f);
    read_conf_fresa(f);
    FRESAON(f);
    for(int i = 0; i < qtde; i++){
        #ifdef RASP_OS
            delay(i);
        #else
            sleep(1);
        #endif

    } 
    FRESAOFF(f);
    printf("Deu certo\n");
    return 0;
}
