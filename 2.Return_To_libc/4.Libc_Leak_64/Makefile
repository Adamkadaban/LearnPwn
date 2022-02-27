CC=gcc
CFLAGS= -w -O0 -no-pie -fno-stack-protector

all: pwn.c
	$(CC) pwn.c $(CFLAGS) -o pwn

clean:
	rm -f pwn
