#include <stdlib.h>
#include <stdio.h>
#include "gcode.h"
#include <string.h>
#ifdef RASP_OS
    #include <wiringPi.h>
#endif


int testing_get_gcode(){
    char c[] = "testando  G01 X32";
    gcommand g;
    g.line = c;
    get_gcode(&g);
    printf("Teste get_code\n");
    if(strcmp(g.gcode, "G01") == 0){
        printf("Passou no teste\n");
    }else{
        printf("Teste falhou esperava por G01 encontrou %s\n", g.gcode);
    }
    return 0;

}

int testing_set_G01_coordenates(){
    char c[] = "testando  G01 X32 Z33.4";
    gcommand g;
    g.line = c;
    get_gcode(&g);
    set_G01_coordenates(&g);
    printf("Teste G01 coordenates\n");
    if(g.x == 32 && g.z == 33.4){
        printf("Passou no teste\n");
    }else{
        printf("Teste falhou esperava por G01 encontrou %s\n", g.gcode);
    }
    return 0;

}


int main(int argv, char *argc[]){
    #ifdef RASP_OS
    wiringPiSetup();
    #endif    
    testing_get_gcode();
    testing_set_G01_coordenates();
    char c[] = "testando  G01 X32";
    gcommand g;
    g.line = c;
    get_gcode(&g);
    set_G01_coordenates(&g);
    printf("A coordenada X: %lf\n", g.x);
    return 0;
}
