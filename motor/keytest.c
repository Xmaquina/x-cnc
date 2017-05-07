#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/time.h>
#include <termios.h>
#include <signal.h>
#include "motor.h"
#include "../osmacros.h"
#ifdef RASP_OS
    #include <wiringPi.h>
#endif

void handler (int sig){
  printf ("nexiting...(%d)n", sig);
  exit (0);
}
 
void perror_exit (char *error){
  perror (error);
  handler (9);
}
 
int main (int argc, char *argv[]){
    struct input_event ev[64];
    int fd, rd, value, size = sizeof (struct input_event);
    char name[256] = "Unknown";
    char *device = NULL;

    //Setup check
    if (argv[1] == NULL){
      printf("Please specify (on the command line) the path to the dev event interface devicen");
      exit (0);
    }

    if ((getuid ()) != 0)
    printf ("You are not root! This may not work...\n");

    if (argc > 1)
    device = argv[1];

    //Open Device
    if ((fd = open (device, O_RDONLY)) == -1){
    printf ("%s is not a vaild device.\n", device);
    exit(0);
    }

    //Print Device Name
    ioctl (fd, EVIOCGNAME (sizeof (name)), name);
    printf ("Reading From : %s (%s)\n", device, name);

    #ifdef RASP_OS
    wiringPiSetup();    
    #endif
    motor *m, *m1;
    alloc_motor(&m);
    alloc_motor(&m1);
    read_conf(m, X_AXIS);
    read_conf(m1, Y_AXIS);
    if(m == NULL){
        printf("You have to allocated it\n");
    }
    setup_motor(m);
    set_sixteenth_step(m);
    while (1){
      if ((rd = read (fd, ev, size * 64)) < size){
          perror_exit ("read()");      
      }
      value = ev[0].value;

      if (value != ' ' && ev[1].value == 1 && ev[1].type == 1){ // Only read the key press event
        printf ("Code[%d]\n", (ev[1].code));
        if(ev[1].code == 106){
            FORWARD(m);
            MOVE(m);
        }
        if(ev[1].code == 105){
            BACKWARD(m);
            MOVE(m);
        }
      }
    }
 
  return 0;
} 
