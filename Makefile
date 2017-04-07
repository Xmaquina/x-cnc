#
#   Makefile
#
CFLAGS= -g -Wall -std=c99

CC=gcc

TARGET=x-cnc

MAIN= main.c

all = $(TARGET)

%.o: %.c 
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): main.o motor.o
	$(CC) $(CFLAGS) -o $@ $^


