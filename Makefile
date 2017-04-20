#
#   Makefile
#
WIRINGFLAG  = -l wiringPi
UNAME       = $(shell uname)
CC          = gcc
ifeq ($(UNAME), Darwin)
	CFLAGS=-g -Wall -std=c99
else
	CFLAGS=-g -Wall -std=c99 $(WIRINGFLAG)
endif

TARGET   = x-cnc
MAIN     = main.c
MOTOR    = motor.o 
GCODE    = gcode.o

all = $(TARGET)


$(TARGET): main.o $(MOTOR) $(GCODE)
	$(CC) $(CFLAGS) -o $@ $^

$(MOTOR) : motor.c motor.h xcncmacros.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(GCODE) : gcode/gcode.c gcode/gcode.h xcncmacros.h
	$(CC) $(CFLAGS) -c -o $@ $<

main.o : main.c $(MOTOR)
	$(CC) $(CFLAGS)  -c -o $@ $<

clean:
	rm *.o    
	rm x-cnc
