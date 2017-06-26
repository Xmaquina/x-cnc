#include <stdlib.h>
#include <stdio.h>
#include "gcode.h"
#include <string.h>
#ifdef RASP_OS
    #include <wiringPi.h>
#endif

int testing_isNULL(){
    printf("Teste de achar gcode\n");
    char c[] = "testando X32";
    gcommand g;
    g.line = c;
    g.gcode = NULL;
    set_coordenates(&g);
    printf("Teste isNULL\n");
    if(isNULL(&g)){
        printf("Passou no teste\n");
    }else{
        printf("Teste falhou o gcode e %s\n", g.gcode);
    }
    return 0;

}



int testing_get_gcode(){
    printf("Teste de achar gcode\n");
    char c[] = "testando  G1 X32";
    gcommand g;
    g.line = c;
    get_gcode(&g);
    printf("Teste get_code\n");
    if(strcmp(g.gcode, G01) == 0){
        printf("Passou no teste\n");
    }else{
        printf("Teste falhou esperava por G01 encontrou %s\n", g.gcode);
    }
    return 0;

}
int testing_has_gcode(){
    printf("Teste has gcode\n");
    char c[] = "testando  G01 X32";
    gcommand g;
    g.line = c;
    if(hasGCODE(&g)){
        printf("Passou no teste\n");
    }else{
        printf("Teste esperava acusar Gcode\n");
    }
    return 0;

}
int testing_hasonecoordenate(){
    printf("Teste has one coordenate\n");
    char c[] = "testando  G01 Y3";
    gcommand g;
    g.line = c;
    if(hasonecoordenate(&g, "Y")){
        printf("Passou no teste\n");
    }else{
        printf("Teste deveria ter so uma coordenada\n");
    }
    return 0;

}
int testing_set_G01_coordenates(){
    char c[] = "testando  G01 X32 Z33.4";
    gcommand g;
    g.line = c;
    get_gcode(&g);
    set_coordenates(&g);
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
    testing_isNULL();
    testing_get_gcode();
    testing_set_G01_coordenates();
    testing_has_gcode();
    testing_hasonecoordenate();
    char c[] = "testando  G01 X32";
    gcommand g;
    g.line = c;
    get_gcode(&g);
    set_coordenates(&g);
    printf("A coordenada X: %lf\n", g.x);
    return 0;
}
