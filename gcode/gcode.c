#include "gcode.h"
#include "../xcncmacros.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

gc_list * create_list(){
    gc_list *gl = (gc_list *) malloc(sizeof(gc_list));
    if(gl != NULL){
        gl->size = 0;
        gl->head = NULL;
    }
    return gl;
}

gc_node * create_node(gcommand *gc){
    gc_node * gn = (gc_node *) malloc(sizeof(gc_node));
    if(gn != NULL){
        gn->elem = gc;
        gn->next = NULL; 
    }
    return gn;
}

int add(gc_list *gl, gcommand *gc){
    gc_node *new = create_node(gc);

    if(gl->size == 0){
        gl->head = new;
    }else{
        gc_node *last = gl->head;
        while(last->next != NULL){
            last = last->next;
        }
        last->next = new;
    }
    gl->size++;
    return 0;
}

int get_gcode(gcommand *g){
    regex_t regex;
    int reti;
    reti = regcomp(&regex,"(N[0-9]+) (G[0-9]+)", REG_EXTENDED);
    reti = regexec(&regex,g->line, 0, NULL, REG_EXTENDED);
printf("Reti :%d\n",reti);
    if(reti == 0){
        printf("Match");
    }
    regfree(&regex);
printf("Entrou aqui\n");
    char p[3];
    strncpy(p, g->line,1); 
printf("O que foi copiado %s\n", p);
    if(strcmp(p,"N") == 0){
        strncpy(p, g->line+4,3); 
        printf("code %s\n", p);
    }  
    return 1;    
}

int copy_line(gcommand *gc, char *line){
    gc->line = (char *)malloc(sizeof(char) * strlen(line) + 1);
    if(gc->line != NULL){
        strncpy(gc->line, line, strlen(line));
//printf("Line copied: %s", gc->line);
        return 0;
    }
    return 1;
}

int read_gcodefile(char *file_name, gc_list *gl){
    char buffer[255];
    FILE *fp = fopen(file_name, "r");
    if(fp != NULL){
        while(1){
            gcommand *gc = (gcommand *)malloc(sizeof(gcommand));
            if(fgets(buffer, 255,fp) == NULL) break;
//printf("Line read %s", buffer);
            copy_line(gc, buffer);
            add(gl, gc);
//printf("Size list: %d\n", gl->size);  
        }
    }
    fclose(fp);
    return 1;
}
