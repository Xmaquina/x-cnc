#
#   Makefile
#
WIRINGFLAG  = -l wiringPi
UNAME       = $(shell uname)
DISTRO      = $(shell lsb_release -si)
CC          = gcc

ifeq ($(DISTRO), Ubuntu)
	MACROS=
else
	MACROS=../osmacros.h
endif

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
	@echo $(DISTRO)
	$(CC) $(CFLAGS) -o $@ $^

steptest: steptest.o $(MOTOR) 
	$(CC) $(CFLAGS) -o $@ $^

dtest: $(DTEST).o $(MOTOR) 
	$(CC) $(CFLAGS) -o $@ $^


$(MOTOR) : motor.c motor.h ../xcncmacros.h $(MACROS) 
	@echo $(MACROS)
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
