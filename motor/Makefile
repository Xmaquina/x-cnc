#
#   Makefile
#
WIRINGFLAG    = -l wiringPi
CC            = gcc




TARGET     = prog
MAIN       = main.c

.DEFAULT_GOAL := $(TARGET)

include ../Makefile.conf

$(TARGET): main.o $(MOTOR) $(MACROS) $(SENSOR) $(UTIL) 
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

main.o : main.c  
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
