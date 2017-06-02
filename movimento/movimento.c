#include "movimento.h"
#include "../motor/motor.h"
#include "../sensor/sensor.h"
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
#include <errno.h>

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
    setup_step(m, 3);
    int i = 0;
    while(1){
        SREAD(s);
        if(SACTIVE(s)){
          break;
        }
        MOVE(m);
        i++;
        delay(1);
    }
    printf("Voltas:%d ", i);
    setup_step(m, m->set_step);
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
            delay(1);
        }
        if(!SACTIVE(sy)){
            MOVE(ym);
            delay(1);
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
        delay(1);
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
    int voltasx = dx * 1000;
    int voltasy = dy * 1000;
printf("Voltas x %d voltas y %d\n",voltasx, voltasy);
    bresenham1(m, m1, 0, 0, voltasx, voltasy);      
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
