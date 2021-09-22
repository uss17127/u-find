CFLAGS = -g -Wall -Wno-unused-variable

CC = gcc

all: sfind

sfind: sfind.h sfindFunc.c sfind.c
	$(CC) $(CFLAGS) sfind.c sfindFunc.c -o sfind

# generic
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f sfind
	rm -f core *.o a.out
	rm -f DIRECTORY.html
	rm -rf *.dSYM

webclean:
	rm -f DIRECTORY.html
