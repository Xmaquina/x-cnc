#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "tools/motor.h"
#include "gcode/gcode.h"
#include "tools/sensor.h"
#include <string.h>
#include "osmacros.h"
#include "movimento/movimento.h"
#include "tools/cnc.h"
#include <errno.h>
#ifdef RASP_OS
    #include <wiringPi.h>
#endif


int main(int argv, char *argc[]){
    if(argv < 2){
        perror("One argument is needed\n");
        exit(EXIT_FAILURE);
    }
    int exec = 1;
    if(argv == 3){
        exec = atoi(argc[2]);
    }
    printf("exec %d\n", exec);
    int tool = 1;
    if(argv == 4){
        tool = atoi(argc[3]);
    }
    printf("Program name %s\n", argc[0]);
    printf("File name %s\n", argc[1]);
    gc_list * gl = create_list();
    if(gl == NULL){
        perror("List cannot be created");
        exit(EXIT_FAILURE);
    }
    read_gcodefile(argc[1], gl);
    /*
    for(gc_node *it = gl->head; it != NULL; it = it->next){
            print_gcommand(it->elem);  
    }
    */
    #ifdef RASP_OS
        wiringPiSetup();
    #endif
    cnc *c;
    alloc_cnc(&c);
    if(c == NULL){
        fprintf(stderr, "It cannot allocated cnc structure because of %s\n",
            strerror(errno));
        return 1;  
    }   
    read_cnc(c);
    if(tool == 0){
        c->type_of_work = LASER;
    }else if(tool == 1){
        c->type_of_work = FRESA;
    }else{
        c->type_of_work = LASER;
    }
    //print_motor(c->xm);
    //c->xm = get_motor(x_axis);
    //print_motor(c->xm);
    mover_zero_cnc(c); 
    if(exec == 1){
        ponto p;
        p.x = 0; p.z = 0; p.y = 0;
        printf("Starting trabalho: \n");
        for(gc_node *it = gl->head; it != NULL; it = it->next){
            //printf("Elemento: \n");
            //print_gcommand(it->elem);
            if(it->prev != NULL){
                print_gcommand(it->elem);
                executar(c, it->elem, NULL,&p);
                //printf("Prev: \n");
                //print_gcommand(it->prev->elem);
            }else{
                executar(c, it->elem, NULL, &p);
            }  
        }
    }
    setdown_cnc(c);
    free(c);
    return 0;
}
