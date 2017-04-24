#
#   Makefile
#
WIRINGFLAG  = -l wiringPi
UNAME       = $(shell uname)
CC          = gcc
CV_INCLUDE  = -I/usr/local/include/opencv -I/usr/local/include/opencv2 
CV_LIBS     = -L/usr/local/lib/ -lm  -lopencv_core -lopencv_imgproc \
              -lopencv_highgui -lopencv_ml -lopencv_video \
              -lopencv_features2d -lopencv_calib3d -lopencv_objdetect \
              -lopencv_contrib -lopencv_legacy -lopencv_stitching
 
ifeq ($(UNAME), Darwin)
	CFLAGS=-g -Wall -std=c99
else
	CFLAGS=-g -Wall -std=c99 $(WIRINGFLAG) 
endif

TARGET   = x-cnc
MAIN     = main.c
MOTOR    = motor.o 
GCODE    = gcode.o
TOKEN    = token.o

all = $(TARGET)


$(TARGET): main.o $(MOTOR) $(GCODE) $(TOKEN)
	$(CC) $(CFLAGS) -o $@ $^ $(CV_LIBS)

$(MOTOR) : motor.c motor.h xcncmacros.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(GCODE) : gcode/gcode.c gcode/gcode.h xcncmacros.h $(TOKEN) 
	$(CC) $(CFLAGS) -c -o $@ $< -lm

$(TOKEN) : gcode/token/token.c gcode/token/token.h xcncmacros.h
	$(CC) $(CFLAGS) -c -o $@ $<

main.o : main.c $(MOTOR)
	$(CC) $(CFLAGS)  -c -o $@ $< $(CV_INCLUDE)

clean:
	rm *.o    
	rm x-cnc
