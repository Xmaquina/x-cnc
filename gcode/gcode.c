#include "gcode.h"
#include "../token/token.h"
#include "../xcncmacros.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <math.h>


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
        gn->prev = NULL; 
    }
    return gn;
}

int add(gc_list *gl, gcommand *gc){
    gc_node *new = create_node(gc);

    if(gl->size == 0){
        gl->head = new;
        gl->tail = new;
    }else{
        new->prev = gl->tail;
        gl->tail->next = new;
        gl->tail = new;
    }
    gl->size++;
    return 0;
}

double get_digits_coordenate(gcommand *g, char *coord){
    token *tk = get_digits_after_token(g->line, coord,0 );
    if(tk != NULL){
        //printf("Begin %d End %d\n", tk->begin, tk->end);
        char c[3];
        memset(c,'\0', 3);    
        strncpy(c,g->line+tk->begin, tk->end - tk->begin + 1);
        double r = (double)atoi(c);
        return r;
        //printf("valor convertido: %s %d\n",c, atoi(c));
        //printf("valor convertido: %s\n",c);
    }
    return 0;
}

int set_G01_coordenates(gcommand *g){
    if(!(strcmp(g->gcode, G01) == 0 || strcmp(g->gcode, G00) == 0)){
        return 1;
    }
    //int val = 0;
    double_after_token(g->line, "X",0, &g->x);
    double_after_token(g->line, "Y",0, &g->y);
    double_after_token(g->line, "Z",0, &g->z);
    double_after_token(g->line, "F",0, &g->f);
    //g->x = (double)val;
    //g->x = get_digits_coordenate(g, "X");
    //g->y = get_digits_coordenate(g, "Y");
    //g->z = get_digits_coordenate(g, "Z");
    //g->f = get_digits_coordenate(g, "F");
    
    return 0;
}

int set_gcommand_gcode(gcommand *g, const char * code){
    int len = strlen(code);
    g->gcode = (char *)malloc(sizeof(char) * len);
    if(g->gcode != NULL){
        strcpy(g->gcode, code);
        return 0;
    }
    return 1;
}

int get_gcode(gcommand *g){
    tk_list *tl = create_list_tk();
    if(tl == NULL) exit(EXIT_FAILURE);  
    const char *gcodes[2] = {G01,G00};
    for(int i = 0; i < NR_GCODES; i++){
        get_token(g->line,gcodes[i], tl);
//printf("Size tk %d\n", tl->size);
        if(tl->size > 0){
            set_gcommand_gcode(g, gcodes[i]);
            //int len = strlen(gcodes[i]);
            //g->gcode = (char *)malloc(sizeof(char) * len);
            //strcpy(g->gcode, gcodes[i]);
//printf("Gcode in get_code %s\n", g->gcode);
            free_tk_list(tl);
            break;
        } 
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




int isG01(gcommand *g){
    if(g == NULL) return 0;
    if(strcmp(g->gcode, G01) == 0){
        return 1;
    }
    return 0;
}
int isG00(gcommand *g){
    if(g == NULL) return 0;
    if(strcmp(g->gcode, G00) == 0){
        return 1;
    }
    return 0;
}

int print_gcommand(gcommand *g){
    printf("Gcommand\n");
    printf("Line: %s\n",g->line);
    printf("Gcode: %s\n",g->gcode);
    printf("X: %lf\n",g->x);
    printf("Y: %lf\n",g->y); 
    printf("Z: %lf\n",g->z);
    printf("F: %lf\n",g->f);
    return 1;
}
