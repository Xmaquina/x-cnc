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
    int exec = 1;
    if(argv == 3){
        exec = atoi(argc[2]);
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
        if(hasGCODE(it->elem)){
            get_gcode(it->elem);
            printf("Gcode %s\n", it->elem->gcode);
            set_coordenates(it->elem);
            printf("Coord x: %lf y: %lf z: %lf f: %lf\n", it->elem->x, it->elem->y, it->elem->z, it->elem->f);
        }else if(hasCoordenates(it->elem)){
            if(it->prev != NULL && it->prev->elem->gcode != NULL){
                set_gcode(it->prev->elem, it->elem);
            }
            set_coordenates(it->elem);
            printf("Sem Gcode coord x: %lf y: %lf z: %lf f: %lf\n", it->elem->x, it->elem->y, it->elem->z, it->elem->f);

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
    if(exec == 1){
        ponto p;
        p.x = 0; p.z = 0; p.y = 0;
        printf("Starting trabalho: \n");
        for(gc_node *it = gl->head; it != NULL; it = it->next){
            //printf("Elemento: \n");
            //print_gcommand(it->elem);
            if(it->prev != NULL){
                executar(c, it->elem, it->prev->elem,&p);
                //printf("Prev: \n");
                //print_gcommand(it->prev->elem);
            }else{
                executar(c, it->elem, NULL, &p);
            }  
        }
    }else{
        for(gc_node *it = gl->head; it != NULL; it = it->next){
            print_gcommand(it->elem);  
        }
        
    }

    return 0;
}
