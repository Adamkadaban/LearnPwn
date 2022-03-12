CC=gcc
CFLAGS= -w -O0 -no-pie -fstack-protector-all -m32

all: pwn.c
	$(CC) pwn.c $(CFLAGS) -o pwn

clean:
	rm -f pwn
