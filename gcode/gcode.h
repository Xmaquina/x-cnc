#ifndef GCODE_H
#define GCODE_H

#define G01 "G1"
#define G00 "G0"
#define G04 "G04"
#define G40 "G40"
#define G49 "G49"
#define G80 "G80"
#define G54 "G54"
#define G90 "G90"
#define G21 "G21"
#define G61 "G61"
#define M   "M"
#define S   "S"
#define NR_GCODES 12

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
int set_coordenates(gcommand *g);
int read_gcodefile(char *file_name,gc_list *gl); 
int isG01(gcommand *g);
int isG00(gcommand *g);
int isX(gcommand *g);
int isY(gcommand *g);
int isZ(gcommand *g);
int print_gcommand(gcommand *g);
int isComment(gcommand *g);
int hasGCODE(gcommand *g);
int hasCoordenates(gcommand *g);
int set_gcode(gcommand *bf, gcommand *g);
int hasonecoordenate(gcommand *g, char *coordenate);
#endif
