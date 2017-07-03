#include "movimento.h"
#include "../tools/cnc.h"
#include "../tools/motor.h"
#include "../tools/laser.h"
#include "../tools/fresa.h"
#include "../tools/sensor.h"
#include "../gcode/gcode.h"
#include "../xcncmacros.h"
#include "../osmacros.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "../token/token.h"

#ifdef RASP_OS 
    #include<wiringPi.h>
#endif
#include<errno.h>

int mover_para_ponto_zero(motor *m){
    sensor *s;
    alloc_sensor(&s);
    if(m->axis == x_axis){
       read_conf_sensor(s, SX_AXIS);    
       FORWARD(m);
    }
    if(m->axis == y_axis){
       read_conf_sensor(s, SY_AXIS);    
       FORWARD(m);
    }
    if(m->axis == z_axis){
       read_conf_sensor(s, SZ_AXIS);    
       FORWARD(m);
    }
    printf("axis: %d\n", m->axis);
    setup_step(m, 3);
    int i = 0;
    while(1){
        SREAD(s);
        if(SACTIVE(s)){
          break;
        }
        MOVE(m);
        i++;
        #ifdef RASP_OS 
        delay(DELAY_TIME);
        #endif
    }
    printf("Voltas:%d ", i);
    setup_step(m, m->set_step);
    return 1;
}

int mover_zero_cnc(cnc *c){
    FORWARD(c->ym);
    FORWARD(c->xm);
    FORWARD(c->zm);
    while(1){
        SREAD(c->ym->s);
        SREAD(c->zm->s);
        SREAD(c->xm->s);
printf("Active x sensor %d\n", SACTIVE(c->xm->s));
printf("Active z sensor %d\n", SACTIVE(c->zm->s));
        if(SACTIVE(c->xm->s) && SACTIVE(c->zm->s) && SACTIVE(c->ym->s)){
          break;
        }
        if(!SACTIVE(c->ym->s)){
            MOVE(c->ym);
            #ifdef RASP_OS 
            delay(1);
            #endif
        }
        if(!SACTIVE(c->zm->s)){
            MOVE(c->zm);
            #ifdef RASP_OS 
            delay(1);
            #endif
        }
        if(!SACTIVE(c->xm->s)){
            MOVE(c->xm);
            #ifdef RASP_OS 
            delay(1);
            #endif
        }
    }
    return 1;
    
}



int executar(cnc *c, gcommand *g,gcommand *bg, ponto *p){
    int x = 0, z = 0, y = 0;
    if(isNULL(g) || isG01(g) || isG00(g)){ 
        if(isZ(g)){
            z = 1;
            if(isLaser(c)){
                printf("Porque nao para %lf %lf\n",g->z, p->z); 
                if(g->z - p->z > 0){
                    LASEROFF(c->l);
                }else{
                    LASERON(c->l);
                }
            }else{
                move_reta2(c->zm, c->ym, p->z, p->y, g->z, g->y);
            }
        }else if(isF(g)){
            printf("F\n");
        }else if(isY(g)){
            y = 1;
            move_reta2(c->xm, c->ym, p->x, p->y, p->x, g->y);
        }else if(isX(g)){
            move_reta2(c->xm, c->ym, p->x, p->y, g->x, p->y);
            x = 1;
        }else{
            x = 1; y = 1;
            move_reta2(c->xm, c->ym, p->x, p->y, g->x, g->y);
        }
    }
    if(isG40(g) || isG49(g) || isG80(g) || isG54(g) || isG90(g) || isG21(g) || isG61(g)){
        printf("gcomand sem nada\n");
    }
    if(x) p->x = g->x;
    if(y) p->y = g->y;
    if(z) p->z = g->z;
    return 1;

}
int mover_zero(motor *xm, motor *ym, sensor *sx, sensor *sy){
    FORWARD(xm);
    FORWARD(ym);
    setup_step(xm, 3);
    setup_step(ym, 3);
    int i = 0;
    while(1){
        SREAD(sx);
        SREAD(sy);
        if(SACTIVE(sx) && SACTIVE(sy)){
          break;
        }
        if(!SACTIVE(sx)){
            MOVE(xm);
            #ifdef RASP_OS 
            delay(DELAY_TIME);
            #endif
        }
        if(!SACTIVE(sy)){
            MOVE(ym);
            #ifdef RASP_OS 
            delay(DELAY_TIME);
            #endif
        }
        i++;
    }
    printf("Voltas:%d ", i);
    setup_step(xm, xm->set_step);
    setup_step(ym, ym->set_step);
    return 1;
}

int mover_motor_um_eixo(motor *m, double mm){
    int direction = mm < 0 ? 1 : 0;
printf("Direction %d\n", direction);
    int voltas = mm >= 0 ? 1000 * mm: 1000 * mm * (-1);
    move_motor(m,direction, voltas);
    return 1;

}

void swap(double* a, double* b){
printf("passou aqui\n"); 
    double temp = *(a);
    *(a) = *(b);
    *(b) = temp;
printf("temp %lf\n",temp);
}

int move_reta(motor *m, motor *m1, double x, double y, double x1, double y1){
    x > x1 ? FORWARD(m) : BACKWARD(m);
    y > y1 ? FORWARD(m1) : BACKWARD(m1);
    x > x1 ? swap(&x,&x1) : 0;
printf("y %lf\n",y);
printf("y1 %lf\n",y1);
    y > y1 ? swap(&y,&y1) : 0;
    double dx = x1 - x;
    double dy = y1 - y;
    double voltas = dy > dx ? dy : dx;
    double steps = dy > dx ? dx/dy : dy/dx;
    setup_step(m,2);
    setup_step(m1,1);
printf("Steps %lf\n",steps);
printf("Voltas %lf\n",voltas);
printf("x %lf\n",x);
printf("x1 %lf\n",x1);
printf("y %lf\n",y);
printf("y1 %lf\n",y1);
    int voltas_convertidas = voltas * 1000;
printf("voltas convertidas %d\n",voltas_convertidas);
    for(int i = 0; i < voltas_convertidas; i++){
        MOVE(m);
        MOVE(m1);
        #ifdef RASP_OS 
        delay(DELAY_TIME);
        #endif
    }      
    return 0;
}

int move_reta2(motor *m, motor *m1, double x, double y, double x1, double y1){
    x > x1 ? FORWARD(m) : BACKWARD(m);
    y > y1 ? FORWARD(m1) : BACKWARD(m1);
    x > x1 ? swap(&x,&x1) : 0;
printf("y %lf\n",y);
printf("y1 %lf\n",y1);
    y > y1 ? swap(&y,&y1) : 0;
printf("x %lf y %lf x1 %lf y1 %lf\n", x, y, x1, y1);
    double dy = y1 - y;
    double dx = x1 - x;
    int voltasx = dx * VOLTAS_X;
    int voltasy = dy * VOLTAS_Y;
printf("Voltas x %d voltas y %d\n",voltasx, voltasy);
    if(voltasx == 0 && voltasy > 0){
        bresenham1(m1, m, 0, 0, voltasy, voltasx);      
    }else if(voltasx > 0 && voltasy >= 0){
        bresenham1(m, m1, 0, 0, voltasx, voltasy);
    }      
    return 0;
}

int move_circulo(motor *m, motor *m1, double x, double y, double r){
    //x > x1 ? FORWARD(m) : BACKWARD(m);
    //y > y1 ? FORWARD(m1) : BACKWARD(m1);
    //x > x1 ? swap(&x,&x1) : 0;
printf("x %lf\n",x);
printf("y %lf\n",y);
    double val = PI/180;
    double x0, y0, x1, y1;
    x0 = x + r * cos(0 * val);
    y0 = y + r * sin(0 * val);
    for(int i = 1; i <= 180; i++){  
        x1 = x + r * cos(i * val);
        y1 = y + r * sin(i * val);
        move_reta2(m, m1, x0, y0, x1, y1);
        x0 = x1;
        y0 = y1;
    }      
    return 0;
}

int move_circulo_eixoy(motor *m, motor *m1, double x, double y, double r){
    //x > x1 ? FORWARD(m) : BACKWARD(m);
    //y > y1 ? FORWARD(m1) : BACKWARD(m1);
    //x > x1 ? swap(&x,&x1) : 0;
printf("x %lf\n",x);
printf("y %lf\n",y);
    double val = PI/180;
    double x0, y0, x1, y1;
    x0 = x + r * cos(0 * val);
    y0 = y + r * sin(0 * val);
    for(int i = 1; i <= 180; i++){  
        x1 = x + r * cos(i * val);
        y1 = y + r * sin(i * val);
        move_reta2(m1, m, x0, y0, x1, y1);
        x0 = x1;
        y0 = y1;
    }      
    return 0;
}
