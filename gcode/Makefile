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


TARGET     = prog
MAIN       = main.c
GCODE      = gcode.o 
TOKEN      = token.o 

all = $(TARGET)


$(TARGET): main.o $(GCODE) $(MACROS) $(TOKEN)
	$(CC) $(CFLAGS) -o $@ $^

$(GCODE) : gcode.c gcode.h ../xcncmacros.h $(MACROS) $(TOKEN)
	@echo $(MACROS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(TOKEN) : ../token/token.c ../token/token.h ../xcncmacros.h $(MACROS) 
	@echo $(MACROS)
	$(CC) $(CFLAGS) -c -o $@ $<


main.o : main.c $(GCODE) $(MACROS) 
	$(CC) $(CFLAGS)  -c -o $@ $<

clean:
	rm *.o    
	rm $(TARGET)
