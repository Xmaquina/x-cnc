#ifndef GCODE_H
#define GCODE_H

#define G01 "G01"
#define G00 "G00"
#define NR_GCODES 2

struct point_{
    double x;
    double y;
    double z;
};
    
typedef struct point_ point;

struct gcommand_{
    char * line;
    char * gcode;
    int nr;
    double x;
    double y; 
    double z;
    double f;
    
};

typedef struct gcommand_ gcommand;

struct gc_node_{
    gcommand *elem;
    struct gc_node_ *next;
    struct gc_node_ *prev;
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
int set_G01_coordenates(gcommand *g);
int read_gcodefile(char *file_name,gc_list *gl); 
int isG01(gcommand *g);
int isG00(gcommand *g);
int print_gcommand(gcommand *g);
#endif
