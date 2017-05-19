#
#   Makefile
#
WIRINGFLAG  = -lwiringPi
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


TARGET     = prog
MAIN       = main.c
SENSOR     = sensor.o 
UTIL       = util.o 
MACROS     = ../osmacros.h
TOKEN      = token.o 

all = $(TARGET)


$(TARGET): main.o $(SENSOR) $(MACROS) $(UTIL) $(TOKEN)
	@echo $(DISTRO)
	@echo $(R)
	$(CC) $(CFLAGS) -o $@ $^

$(UTIL): ../util/util.c ../util/util.h 
	$(CC) $(CFLAGS) -c -o $@ $<

$(SENSOR) : sensor.c sensor.h ../xcncmacros.h $(MACROS)
	@echo $(MACROS)
	@echo $^
	$(CC) $(CFLAGS) -c -o $@ $< 

main.o : main.c $(SENSOR) $(MACROS) 
	$(CC) $(CFLAGS)  -c -o $@ $<

$(TOKEN) : ../token/token.c ../token/token.h 
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm *.o  
	rm $(TARGET)
