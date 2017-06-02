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
MOTOR      = motor.o 
DTEST      = directiontest
KTEST      = keytest

all = $(TARGET)


$(TARGET): main.o $(MOTOR) $(MACROS) 
	@echo $(DISTRO)
	@echo $(R)
	$(CC) $(CFLAGS) -o $@ $^

steptest: steptest.o $(MOTOR) $(MACROS) 
	$(CC) $(CFLAGS) -o $@ $^

ctest: clocktest.o $(MOTOR) $(MACROS) 
	@echo $(DISTRO)
	@echo $(R)
	$(CC) $(CFLAGS) -o $@ $^

rtest: testreal.o $(MOTOR) $(MACROS) 
	$(CC) $(CFLAGS) -o $@ $^

dtest: $(DTEST).o $(MOTOR) $(MACROS) 
	$(CC) $(CFLAGS) -o $@ $^

ktest: $(KTEST).o $(MOTOR) $(MACROS) 
	$(CC) $(CFLAGS) -o $@ $^ -lrt


$(MOTOR) : motor.c motor.h ../xcncmacros.h $(MACROS) 
	@echo $(MACROS)
	$(CC) $(CFLAGS) -c -o $@ $<

main.o : main.c $(MOTOR) $(MACROS) 
	$(CC) $(CFLAGS)  -c -o $@ $<

steptest.o : steptests.c $(MOTOR) $(MACROS) 
	$(CC) $(CFLAGS)  -c -o $@ $<

clocktest.o : clocktest.c $(MOTOR) $(MACROS) 
	@echo $(DISTRO)
	@echo $(R)
	$(CC) $(CFLAGS)  -c -o $@ $<

testreal.o : testreal.c $(MOTOR) $(MACROS) 
	$(CC) $(CFLAGS)  -c -o $@ $<

testreta.o : testreta.c 
	$(CC) $(CFLAGS)  -c -o $@ $<

$(DTEST).o : $(DTEST).c $(MOTOR) $(MACROS) 
	$(CC) $(CFLAGS)  -c -o $@ $<

$(KTEST).o : $(KTEST).c $(MOTOR) $(MACROS) 
	$(CC) $(CFLAGS)  -c -o $@ $< -lrt

ttest: testreta.o $(MOTOR) $(MACROS)
	@echo $(DISTRO)
	@echo $(R)
	$(CC) $(CFLAGS) -o $@ $^


clean:
	rm *.o ctest ktest dtest rtest    
	rm $(TARGET)
