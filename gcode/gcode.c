#include "gcode.h"
#include "../xcncmacros.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int get_gcode(gcommand *g){
    char p[3];
    strncpy(p, g->line,1); 
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
printf("Line copied: %s", gc->line);
        return 0;
    }
    return 1;
}

int read_gcodefile(char *file_name, gcommand *gcmds){
    char buffer[255];
    FILE *fp = fopen(file_name, "r");
    gcommand *gc = (gcommand *)malloc(sizeof(gcommand));
    if(fp != NULL){
        while(1){
            if(fgets(buffer, 255,fp) == NULL) break;
printf("Line read %s", buffer);
            copy_line(gc, buffer);
        }
    }
    fclose(fp);
    return 1;
}
