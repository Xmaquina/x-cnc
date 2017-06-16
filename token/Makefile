#
#   Makefile
#
CC          = gcc

TARGET   = prog
MAIN     = main.c

.DEFAULT_GOAL := $(TARGET)

include ../Makefile.conf

$(TARGET): main.o $(TOKEN) 
	$(CC) $(CFLAGS) -o $@ $^

main.o : main.c $(TOKEN)
	$(CC) $(CFLAGS)  -c -o $@ $<

clean:
	rm *.o    
	rm x-cnc
