#include "util.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int file_exists(char *name){
    FILE *file;
    if((file = fopen(name, "r"))){
        fclose(file);
        return 1;
    }
    return 0;

}

char* file_name(char *pre, char *suf){
    if(pre == NULL || suf == NULL) return NULL;
    char *r = malloc(sizeof(char) * (strlen(pre) + strlen(suf) + 2));
    strcpy(r, pre);
    strcat(r,suf);
    return r;
}

