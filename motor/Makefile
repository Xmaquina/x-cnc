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


TARGET     = prog
MAIN       = main.c
MOTOR      = motor.o 
DTEST      = directiontest

all = $(TARGET)


$(TARGET): main.o $(MOTOR) 
	$(CC) $(CFLAGS) -o $@ $^

steptest: steptest.o $(MOTOR) 
	$(CC) $(CFLAGS) -o $@ $^

dtest: $(DTEST).o $(MOTOR) 
	$(CC) $(CFLAGS) -o $@ $^


$(MOTOR) : motor.c motor.h ../xcncmacros.h 
	$(CC) $(CFLAGS) -c -o $@ $<

main.o : main.c $(MOTOR)
	$(CC) $(CFLAGS)  -c -o $@ $<

steptest.o : steptests.c $(MOTOR)
	$(CC) $(CFLAGS)  -c -o $@ $<

$(DTEST).o : $(DTEST).c $(MOTOR)
	$(CC) $(CFLAGS)  -c -o $@ $<

clean:
	rm *.o    
	rm $(TARGET)
