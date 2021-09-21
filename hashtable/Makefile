# Makefile for 'hashtable' module
#
# Annabel Revers, February 2021

PROG = hashtabletest
OBJS = hashtabletest.o hashtable.o set.o jhash.o
LIBS =

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../lib -I../set
CC = gcc
MAKE = make

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

hashtabletest.o: hashtable.h 
hashtable.o: hashtable.h jhash.h set.h
set.0: set.h
jhash.o: jhash.h


.PHONY: test valgrind clean

# expects a file `testing.out` to exist; it can contain any text.
test: $(PROG) testing.out
	./$(PROG) < testing.out

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f $(PROG)

