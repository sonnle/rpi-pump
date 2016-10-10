all: control.c
	gcc -o control.out control.c -lpigpio -lrt -lpthread

debug:
	gcc -o control.out control.c -lpigpio -lrt -lpthread -DDEBUG=1

clean:
	$(RM) control.out
