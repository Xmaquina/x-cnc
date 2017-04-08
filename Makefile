#
#   Makefile
#
CFLAGS= -g -Wall -std=c99
WIRINGFLAG = -l wiringPi

CC=gcc

TARGET   = x-cnc
MAIN     = main.c
MOTOR    = motor.o 

all = $(TARGET)


$(TARGET): main.o $(MOTOR)
	$(CC) $(CFLAGS) $(WIRINGFLAG) -o $@ $^

$(MOTOR) : motor.c motor.h
	$(CC) $(CFLAGS) $(WIRINGFLAG) -c -o $@ $<

main.o : main.c $(MOTOR)
	$(CC) $(CFLAGS) $(WIRINGFLAG) -c -o $@ $<

clean:
	rm *.o    
	rm x-cnc
