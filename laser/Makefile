#
#   Makefile
#
WIRINGFLAG  = -lwiringPi
CC          = gcc


TARGET     = prog
MAIN       = main.c

.DEFAULT_GOAL := $(TARGET)

include ../Makefile.conf


$(TARGET): main.o $(LASER) $(MACROS) $(UTIL)
	@echo $(DISTRO)
	@echo $(R)
	$(CC) $(CFLAGS) -o $@ $^


main.o : main.c  
	$(CC) $(CFLAGS)  -c -o $@ $<

clean:
	rm *.o  
	rm $(TARGET)
