CC = gcc
CFLAGS = -o control.out -lpigpio -lrt -lpthread
all: control.c
	$(CC) $(CFLAGS) control.c

debug:
	$(CC) $(CFLAGS) control.c -DDEBUG=1

clean:
	$(RM) control.out
