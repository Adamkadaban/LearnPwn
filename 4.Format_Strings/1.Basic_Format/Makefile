CC=gcc
CFLAGS= -w -O0 -Wl,-z,relro,-z,now -fstack-protector-all

all: pwn.c
	$(CC) pwn.c $(CFLAGS) -o pwn

clean:
	rm -f pwn
