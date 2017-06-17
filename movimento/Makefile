#
#   Makefile
#
WIRINGFLAG  = -lwiringPi -lm 
CC          = gcc

TARGET = prog

.DEFAULT_GOAL := $(TARGET)

include ../Makefile.conf

$(TARGET): main.o $(MOTOR) $(MACROS) $(SENSOR) $(MOVIMENTO) $(FRESA) $(LASER) $(UTIL) $(CNC) 
	@echo $(DISTRO)
	@echo $(R)
	$(CC) $(CFLAGS) -o $@ $^ -lm

test: testyvoltas.o $(MOTOR) $(MACROS) $(SENSOR) $(MOVIMENTO) $(UTIL)
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
