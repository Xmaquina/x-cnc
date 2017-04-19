#
#   Makefile
#
CFLAGS= -g -Wall -std=c99
WIRINGFLAG = -l wiringPi

CC=gcc

TARGET   = x-cnc
MAIN     = main.c
MOTOR    = motor.o 
GCODE    = gcode.o

all = $(TARGET)


$(TARGET): main.o $(MOTOR) $(GCODE)
	$(CC) $(CFLAGS) $(WIRINGFLAG) -o $@ $^

$(MOTOR) : motor.c motor.h xcncmacros.h
	$(CC) $(CFLAGS) $(WIRINGFLAG) -c -o $@ $<

$(GCODE) : gcode/gcode.c gcode/gcode.h xcncmacros.h
	$(CC) $(CFLAGS) $(WIRINGFLAG) -c -o $@ $<

main.o : main.c $(MOTOR)
	$(CC) $(CFLAGS) $(WIRINGFLAG) -c -o $@ $<

clean:
	rm *.o    
	rm x-cnc
