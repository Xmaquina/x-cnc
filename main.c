#include <stdlib.h>
#include <stdio.h>
#include "motor.h"
#include "gcode/gcode.h"
#include <string.h>



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
