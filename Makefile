#
#   Makefile
#
WIRINGFLAG  = -l wiringPi
CC          = gcc


TARGET   = x-cnc
MAIN     = main.c
all = $(TARGET)

.DEFAULT_GOAL := $(TARGET)

include Makefile.conf

$(TARGET): main.o $(MOTOR) $(MACROS) $(SENSOR) $(MOVIMENTO) $(FRESA) $(LASER) $(UTIL) $(CNC) $(GCODE) $(TOKEN)  
	$(CC) $(CFLAGS) -o $@ $^ -lm

main.o : main.c 
	$(CC) $(CFLAGS)  -c -o $@ $< 

clear:
	rm *.o

clean:
	rm *.o    
	rm x-cnc
