#include "gcode.h"
#include "token/token.h"
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

int sem_nome(gcommand *g){
    regex_t regex;
    int reti;
    size_t matches = 6;
    regmatch_t groups[6];
    const char *gcodes[2] = {G01,G00};
    for(int i = 0; i < NR_GCODES; i++){
        char c[12] = ".*(G01).*";
        char b[10] = ".*(";
        strcat(b,gcodes[i]);
        strcat(b,").*\0");
        if(strcmp(b,c) == 0){
printf("Iguais\n");
        }else if(strcmp(b,c) < 0){
printf("b Menor\n");
        }else{
printf("b Maior\n");
        }   
printf("Regex: b: %s c: %s\n",b,c);
        reti = regcomp(&regex,b, REG_EXTENDED);
printf("Reti: %d\n",reti);
        reti = regexec(&regex,g->line, matches, groups, REG_EXTENDED);
printf("Reti: %d %d\n",reti, REG_NOMATCH);
        if(reti == 0){
            printf("Match\n");
            printf("Line %s\n", g->line);
            for(int i = 0; i < matches; i++){
                printf("b: %d e: %d\n", groups[i].rm_so, groups[i].rm_eo);
            }
        }
        regfree(&regex);
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
            int len = strlen(gcodes[i]);
            g->gcode = (char *)malloc(sizeof(char) * len);
            strcpy(g->gcode, gcodes[i]);
//printf("Gcode in get_code %s\n", g->gcode);
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
