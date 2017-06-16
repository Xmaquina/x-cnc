#
#   Makefile
#
WIRINGFLAG  = -lwiringPi -lm 
UNAME       = $(shell uname)
DISTRO      = $(shell lsb_release -si)
CC          = gcc

ifeq ($(DISTRO), Ubuntu)
	R=$(shell sed -i 's/RASP_OS/OTHERS/g' '../osmacros.h')
else
	R=$(shell sed -i 's/OTHERS/RASP_OS/g' '../osmacros.h')
endif

ifeq ($(UNAME), Darwin)
	CFLAGS=-g -Wall -std=c99 
else
	CFLAGS=-g -Wall -std=c99 $(WIRINGFLAG) 
endif

DIRSENSOR     = ../sensor
DIRLASER      = ../laser
DIRFRESA      = ../fresa
DIRTOKEN      = ../token
DIRMOTOR      = ../motor
DIRUTIL       = ../util
DIRGCODE      = ../gcode
DIRCONF       = ../conf

TARGET        = prog
MAIN          = main.c
MOTOR         = motor.o 
SENSOR        = sensor
MOVIMENTO     = movimento
CNC           = cnc.o
UTIL          = util.o
FRESA         = fresa.o
LASER         = laser.o

all = $(TARGET)


$(TARGET): main.o $(MOTOR) $(MACROS) sensor.o movimento.o $(FRESA) $(LASER) $(UTIL) $(CNC) 
	@echo $(DISTRO)
	@echo $(R)
	$(CC) $(CFLAGS) -o $@ $^ -lm

test: testyvoltas.o $(MOTOR) $(MACROS) sensor.o movimento.o $(UTIL)
	@echo $(DISTRO)
	@echo $(R)
	$(CC) $(CFLAGS) -o $@ $^

dtest: testpulsos.o $(MOTOR) $(MACROS) sensor.o movimento.o $(UTIL)
	@echo $(DISTRO)
	@echo $(R)
	$(CC) $(CFLAGS) -o $@ $^

qtest: testq.o $(MOTOR) $(MACROS) sensor.o movimento.o $(UTIL)
	@echo $(DISTRO)
	@echo $(R)
	$(CC) $(CFLAGS) -o $@ $^

ttest: testt.o $(MOTOR) $(MACROS) sensor.o movimento.o $(UTIL)
	@echo $(DISTRO)
	@echo $(R)
	$(CC) $(CFLAGS) $(WIRINGFLAG) -o $@ $^ -lm

$(FRESA) : ../fresa/fresa.c 
	@echo $(MACROS)
	@echo $^
	$(CC) $(CFLAGS) -c -o $@ $< 

$(LASER) : ../laser/laser.c 
	@echo $(MACROS)
	@echo $^
	$(CC) $(CFLAGS) -c -o $@ $< 

$(SENSOR).o : $(DIRSENSOR)/$(SENSOR).c    
	$(CC) $(CFLAGS) -c -o $@ $<

$(UTIL): ../util/util.c  
	$(CC) $(CFLAGS) -c -o $@ $<

$(MOVIMENTO).o : $(MOVIMENTO).c    
	$(CC) $(CFLAGS) -c -o $@ $< -lm

$(CNC) : cnc.c    
	$(CC) $(CFLAGS) -c -o $@ $< -lm

$(MOTOR) : ../motor/motor.c 
	@echo $(MACROS)
	$(CC) $(CFLAGS) -c -o $@ $<

main.o : main.c  
	$(CC) $(CFLAGS)  -c -o $@ $<

testyvoltas.o : testyvoltas.c  
	$(CC) $(CFLAGS)  -c -o $@ $<

testpulsos.o : testpulsos.c  
	$(CC) $(CFLAGS)  -c -o $@ $<

testq.o : testq.c  
	$(CC) $(CFLAGS)  -c -o $@ $<

testt.o : testt.c  
	$(CC) $(CFLAGS) -c -o $@ $< -lm

clear:
	rm *.o

clean:
	rm *.o     
	rm $(TARGET) dtest qtest test ttest
