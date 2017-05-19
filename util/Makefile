#
#   Makefile
#
WIRINGFLAG  = -l wiringPi
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


UTIL       = util.o 
DTEST      = directiontest
KTEST      = keytest

all = $(UTIL)

$(UTIL) : util.c util.h ../xcncmacros.h $(MACROS) 
	@echo $(MACROS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm *.o     
