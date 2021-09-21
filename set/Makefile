# Makefile for 'set' module
#
# Annabel Revers, February 2021

PROG = settest
OBJS = settest.o set.o
LIBS =

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../lib
CC = gcc
MAKE = make

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

settest.o: set.h
set.o: set.h

.PHONY: test valgrind clean

# expects a file `testing.out` to exist; it can contain any text.
test: $(PROG) testing.out
	./$(PROG) < testing.out

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f $(PROG)

