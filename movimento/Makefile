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


TARGET        = prog
MAIN          = main.c
MOTOR         = motor.o 
SENSOR        = sensor
DIRSENSOR     = ../sensor
MOVIMENTO     = movimento
UTIL          = util.o
all = $(TARGET)


$(TARGET): main.o $(MOTOR) $(MACROS) sensor.o movimento.o $(UTIL)
	@echo $(DISTRO)
	@echo $(R)
	$(CC) $(CFLAGS) -o $@ $^

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

$(SENSOR).o : $(DIRSENSOR)/$(SENSOR).c    
	$(CC) $(CFLAGS) -c -o $@ $<

$(UTIL): ../util/util.c ../util/util.h 
	$(CC) $(CFLAGS) -c -o $@ $<

$(MOVIMENTO).o : $(MOVIMENTO).c    
	$(CC) $(CFLAGS) -c -o $@ $<

$(MOTOR) : ../motor/motor.c ../motor/motor.h ../xcncmacros.h $(MACROS) 
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

clean:
	rm *.o     
	rm $(TARGET) dtest qtest test
