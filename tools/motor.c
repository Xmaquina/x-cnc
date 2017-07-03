#include "motor.h"
#include "../xcncmacros.h"
#include "../osmacros.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../token/token.h"
#include "../util/util.h"

#ifdef RASP_OS 
    #include<wiringPi.h>
#endif
#include <errno.h>

int alloc_motor(motor **m){
    *m = (motor *)malloc(sizeof(motor));
    if(*m == NULL){
        fprintf(stderr, "It cannot alloccate motor structure because %s\n",
                strerror(errno)); 
        return 1;
    }
    return 0;   
}
char * type_axis(motor *m){
    if(m->axis == X_AXIS){
        return CX_AXIS;
    }else if(m->axis == Y_AXIS){
        return CY_AXIS;
    }else if(m->axis == Z_AXIS){
        return CZ_AXIS;
    }
    return "";
}

char * type_axis_c(motor_axis m){
    if(m == X_AXIS){
        return CX_AXIS;
    }else if(m == Y_AXIS){
        return CY_AXIS;
    }else if(m == Z_AXIS){
        return CZ_AXIS;
    }
    return "";
}

char * motor_file_name(motor *m){
    char * f = file_name(CONFDIR, "stepper-motor-");
    char * r = malloc(sizeof(char) * 120);
    strcpy(r,f);
    strcat(r, type_axis(m));
    return r;
}
int motor_file_exists(motor *m){
    FILE *file;
    char *fname = motor_file_name(m);
    if ((file = fopen(fname, "r"))){
        fclose(file);
        return 1;
    }
    return 0;
}

int print_motor(motor *m){
    printf("Motor\n");
    printf("Angle: %lf\n", m->step);
    printf("Pin direction: %d\n", m->pin_direction );
    printf("Pin Step: %d\n", m->pin_step );
    printf("Pin Limit: %d\n", m->pin_limit );
    printf("Pin ms1: %d\n", m->pin_ms1 );
    printf("Pin ms2: %d\n", m->pin_ms2 );
    printf("Pin ms3: %d\n", m->pin_ms3 );
    printf("set step: %d\n", m->set_step );
    printf("driver: %d\n", m->driver );
    return 1;
}

int read_conf(motor *m, int motor){
    if(m == NULL){ exit(EXIT_FAILURE); };
    m->axis = motor;
    FILE *fp;
    if(motor_file_exists(m)){
        fp = fopen(motor_file_name(m), "r");
    }else{
        fp = fopen("conf/stepper-motor", "r");
    }
    if(fp == NULL){
        fprintf (stderr, "Couldn't open file conf/stepper-motor; %s\n",
                 strerror (errno));
        exit (EXIT_FAILURE);
    }
    char buffer[255];
    double angle = 0;
    int value = 0;
    fscanf(fp, "%s = %lf", buffer, &angle);
    if(strcmp(buffer, "angle") == 0){
        m->step = angle;
    }
    for(int i = 0; i < 8; i++){
        fscanf(fp, "%s = %d", buffer, &value);
        if(strcmp(buffer, DIRECTION) == 0){
            m->pin_direction = (int)value;
        }
        if(strcmp(buffer, STEP) == 0){
            m->pin_step = (int)value;
        }
        if(strcmp(buffer, LIMIT) == 0){
            m->pin_limit = (int)value;
        }
        if(strcmp(buffer, MS1) == 0){
            m->pin_ms1 = (int)value;
        }
        if(strcmp(buffer, MS2) == 0){
            m->pin_ms2 = (int)value;
        }
        if(strcmp(buffer, MS3) == 0){
            m->pin_ms3 = (int)value;
        }
        if(strcmp(buffer, SET_STEP) == 0){
            m->set_step = (int)value;
        }
        if(strcmp(buffer, DRIVER) == 0){
            m->driver = (int)value;
        }
    }
    print_motor(m);
    fclose(fp); 
    
   return 0; 

}

int set_eighth_step(motor *m){
#ifdef RASP_OS 
    digitalWrite(m->pin_ms1, HIGH);
    digitalWrite(m->pin_ms2, HIGH);
    digitalWrite(m->pin_ms3, LOW);
#endif
    return 0;

}

int set_sixteenth_step(motor *m){
#ifdef RASP_OS 
    digitalWrite(m->pin_ms1, HIGH);
    digitalWrite(m->pin_ms2, HIGH);
    digitalWrite(m->pin_ms3, HIGH);
#endif
    return 0;

}
int set_quarter_step(motor *m){
#ifdef RASP_OS 
    digitalWrite(m->pin_ms1, LOW);
    digitalWrite(m->pin_ms2, HIGH);
    digitalWrite(m->pin_ms3, LOW);
#endif
    return 0;

}

int set_half_step(motor *m){
#ifdef RASP_OS 
    digitalWrite(m->pin_ms1, HIGH);
    digitalWrite(m->pin_ms2, LOW);
    digitalWrite(m->pin_ms3, LOW);
#endif
    return 0;

}

int set_full_step(motor *m){
#ifdef RASP_OS 
    digitalWrite(m->pin_ms1, LOW);
    digitalWrite(m->pin_ms2, LOW);
    digitalWrite(m->pin_ms3, LOW);
#endif
    return 0;

}

int setup_step(motor *m, int step){
    if(step == 1){
        printf("PAssou aqui\n");
        set_sixteenth_step(m);
    }
    if(step == 2){
        printf("PAssou aqui 2\n");
        set_eighth_step(m);
    }
    if(step == 3){
        set_quarter_step(m);
    }
    if(step == 4){
        set_half_step(m);
    }
    if(step == 5){
        set_full_step(m);  
    }
    return 1;
}
int setup_motor(motor *m){
#ifdef RASP_OS 
    pinMode(m->pin_step, OUTPUT);
    pinMode(m->pin_direction, OUTPUT);
    pinMode(m->pin_ms1, OUTPUT);
    pinMode(m->pin_ms2, OUTPUT);
    pinMode(m->pin_ms3, OUTPUT);
    if(m->set_step == 1){
        printf("PAssou aqui\n");
        set_sixteenth_step(m);
    }
    if(m->set_step == 2){
        printf("PAssou aqui 2\n");
        set_eighth_step(m);
    }
    if(m->set_step == 3){
        set_quarter_step(m);
    }
    if(m->set_step == 4){
        set_half_step(m);
    }
    if(m->set_step == 5){
        set_full_step(m);  
    }
#endif
    return 0;

}

int setdown_motor(motor *m){
#ifdef RASP_OS 
    digitalWrite(m->pin_step, LOW);
    digitalWrite(m->pin_direction, LOW);
    digitalWrite(m->pin_ms1, LOW);
    digitalWrite(m->pin_ms2, LOW);
    digitalWrite(m->pin_ms3, LOW);
#endif
    return 0;

}


int move_motor(motor *m, int direction, int voltas){
    if(direction == 0){
        BACKWARD(m);
    }else{
        FORWARD(m);
    }
printf("Voltas: %d\n", voltas);
    for(int i = 0; i < voltas; i++){
        MOVE(m);
        #ifdef RASP_OS 
        delay(DELAY_TIME);
        #endif
    }
    return 0;
    
}

void bresenham1(motor *mx, motor *my, int x1, int y1, int x2, int y2){        
        int slope;
        int dx, dy, incE, incNE, d, x, y;
        // Onde inverte a linha x1 > x2       
        if (x1 > x2){
            bresenham1(mx, my, x2, y2, x1, y1);
             return;
        }        
        dx = x2 - x1;
        dy = y2 - y1;
    
        if (dy < 0){            
            slope = -1;
            dy = -dy;
        }
        else{            
           slope = 1;
        }
//print_motor(mx);
        // Constante de Bresenham
        incE = 2 * dy;
        incNE = 2 * dy - 2 * dx;
        d = 2 * dy - dx;
        y = y1;       
printf("Eixo %s %d\n",type_axis_c(mx->axis), x2);
        for (x = x1; x <= x2; x++){
            MOVE(mx);
            #ifdef RASP_OS 
            delay(DELAY_TIME);
            #endif
            if (d <= 0){
              d += incE;
            }
            else{
              d += incNE;
//printf("y no algoritmos %d\n",y);
              y += slope;
              MOVE(my);
              #ifdef RASP_OS 
              delay(DELAY_TIME);
              #endif
            }
        }
  }

motor* get_motor(motor_axis axis){
    motor *m;
    alloc_motor(&m);
    if(m == NULL){
        exit(1);
    }
    alloc_sensor(&m->s);
    if(m->s == NULL){
        exit(1);
    }
    if(axis == x_axis){
        read_conf(m, X_AXIS);
        read_conf_sensor(m->s, SX_AXIS);
    }
    if(axis == y_axis){
        read_conf(m, Y_AXIS);
        read_conf_sensor(m->s, SY_AXIS);
    }
    if(axis == z_axis){
        read_conf(m, Z_AXIS);
        read_conf_sensor(m->s, SZ_AXIS);
    }
    return m;
}


    
