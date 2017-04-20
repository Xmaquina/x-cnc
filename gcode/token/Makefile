#
#   Makefile
#
UNAME       = $(shell uname)
CC          = gcc
CFLAGS      = -g -Wall -std=c99

TARGET   = token
MAIN     = main.c
TOKEN    = token.o 

all = $(TARGET)


$(TARGET): main.o $(MOTOR) $(GCODE)
	$(CC) $(CFLAGS) -o $@ $^

$(TOKEN) : token.c token.h 
	$(CC) $(CFLAGS) -c -o $@ $<

main.o : main.c $(TOKEN)
	$(CC) $(CFLAGS)  -c -o $@ $<

clean:
	rm *.o    
	rm x-cnc
