#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "motor/motor.h"
#include "gcode/gcode.h"
#include "sensor/sensor.h"
#include <string.h>
#include "osmacros.h"
#include "movimento/movimento.h"
#include "movimento/cnc.h"
#include <errno.h>
#ifdef RASP_OS
    #include <wiringPi.h>
#endif


int conversao(double distance){
    return 0;    
}

int main(int argv, char *argc[]){
    if(argv < 2){
        perror("One argument is needed\n");
        exit(EXIT_FAILURE);
    }
    printf("Program name %s\n", argc[0]);
    printf("File name %s\n", argc[1]);
    gc_list * gl = create_list();
    if(gl == NULL){
        perror("List cannot be created");
        exit(EXIT_FAILURE);
    }
    read_gcodefile(argc[1], gl);
    for(gc_node *it = gl->head; it != NULL; it = it->next){
//        printf("Line %s", it->elem->line);
        get_gcode(it->elem);
        printf("Gcode %s\n", it->elem->gcode);
        if(strcmp(it->elem->gcode, G01) == 0){
            printf("G01 code\n");
            set_G01_coordenates(it->elem);
            printf("Coord x: %lf y: %lf z: %lf f: %lf\n", it->elem->x, it->elem->y, it->elem->z, it->elem->f);
        }
    }
    
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
    //print_motor(c->xm);
    //c->xm = get_motor(x_axis);
    //print_motor(c->xm);
    ponto p;
    p.x = 0; p.z = 0; p.y = 0;
    printf("Starting trabalho: \n");
    for(gc_node *it = gl->head; it != NULL; it = it->next){
        executar(c, it->elem, NULL,&p);  
    }

    return 0;
}
