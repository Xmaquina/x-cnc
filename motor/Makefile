#
#   Makefile
#
UNAME       = $(shell uname)
CC          = gcc
CFLAGS      = -g -Wall -std=c99

TARGET   = prog
MAIN     = main.c
MOTOR    = motor.o 

all = $(TARGET)


$(TARGET): main.o $(MOTOR) 
	$(CC) $(CFLAGS) -o $@ $^

$(MOTOR) : motor.c motor.h ../xcncmacros.h 
	$(CC) $(CFLAGS) -c -o $@ $<

main.o : main.c $(MOTOR)
	$(CC) $(CFLAGS)  -c -o $@ $<

clean:
	rm *.o    
	rm $(TARGET)
