#ifndef GCODE_H
#define GCODE_H

#define G01 "GO1"
#define G00 "G00"
#define NR_GCODES 2
struct gcommand_{
    char * line;
    char * gcode;
    
};

typedef struct gcommand_ gcommand;

struct gc_node_{
    gcommand *elem;
    struct gc_node_ *next;
};

typedef struct gc_node_ gc_node;

struct gc_list_{
    gc_node *head;
    gc_node *tail;
    unsigned int size;
};

typedef struct gc_list_ gc_list;

gc_list * create_list();

int add(gc_list *gl, gcommand *gc);

int get_gcode(gcommand *g);
int read_gcodefile(char *file_name,gc_list *gl); 
#endif
