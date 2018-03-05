all: lib

PREFIX=arm-none-linux-gnueabi-

CC=$(PREFIX)gcc
AR=$(PREFIX)ar

lib:
	$(CC) -O3 -Wall -c v_math.c
	$(AR) -cvq varmathlib.a v_math.o

main:
	$(CC) -static -o main main.c -Wl,--whole-archive varmathlib.a   -Wl,--no-whole-archive -lm

mainso:
	$(CC) -Wall -L/opt/lib main.c -Wl,-no-as-needed -lvirus -Wl,-no-as-needed -lvarmath -lm -o main

install:
	cp libvarmath.so.1.0 libvirus.so.1.0 /opt/lib/

clean:
	rm *a *o main
