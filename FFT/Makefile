all: fft

PREFIX=arm-none-linux-gnueabi-

CC=$(PREFIX)gcc
AR=$(PREFIX)ar

OBJ = main.o fftmisc.o  fourierf.o
FILE = main.c fftmisc.c  fourierf.c
CFLAGS = -static -O3 -g

fft: ${OBJ} Makefile
	$(CC)  ${CFLAGS} ${OBJ} -o fft -lm -Wl,--whole-archive varmathlib.a   -Wl,--no-whole-archive -lm
fftmisc.o: fftmisc.c
	$(CC) ${CFLAGS} -c fftmisc.c
fourierf.o: fourierf.c
	$(CC) ${CFLAGS} -c fourierf.c
main.o: main.c
	$(CC) ${CFLAGS} -c main.c

lib:
	$(CC) -O3 -Wall -c v_math.c
	$(AR) -cvq varmathlib.a v_math.o

mainso:
	$(CC) -Wall -L/opt/lib main.c -Wl,-no-as-needed -lvirus -Wl,-no-as-needed -lvarmath -lm -o main

install:
	cp libvarmath.so.1.0 libvirus.so.1.0 /opt/lib/


clean:
	rm -rf *.o *a fft output*
