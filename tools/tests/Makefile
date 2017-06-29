#
#   Makefile
#
WIRINGFLAG    = -l wiringPi
CC            = gcc




TARGET     = motor
MAIN       = main.c

.DEFAULT_GOAL := motor laser 

include ../../Makefile.conf

motor: motortest.o $(MOTOR) $(MACROS) $(SENSOR) $(UTIL) 
	@echo $(DISTRO)
	@echo $(R)
	$(CC) $(CFLAGS) -o $@ $^


motortest.o : motortest.c  
	$(CC) $(CFLAGS)  -c -o $@ $<

laser: lasertest.o $(LASER) $(MACROS) $(UTIL)
	$(CC) $(CFLAGS) -o $@ $^

lasertest.o : lasertest.c  
	$(CC) $(CFLAGS)  -c -o $@ $<

sensor: sensortest.o $(SENSOR) $(UTIL)
	$(CC) $(CFLAGS) -o $@ $^

sensortest.o : sensortest.c $(SENSOR) $(MACROS) 
	$(CC) $(CFLAGS)  -c -o $@ $<

fresa: fresatest.o $(FRESA) $(UTIL) 
	@echo $(DISTRO)
	@echo $(R)
	$(CC) $(CFLAGS) -o $@ $^

fresatest.o : fresatest.c 
	$(CC) $(CFLAGS)  -c -o $@ $<

clean:
	rm *.o ctest ktest dtest rtest    
	rm $(TARGET)
