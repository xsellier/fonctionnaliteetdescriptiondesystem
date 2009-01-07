CIBLES = sudoku
SRCS = sudoku.c
LIBS =

PREFIX = /usr

OBJS = $(SRCS:.c=.o)
INCDIR = $(PREFIX)/include
LIBDIR = $(PREFIX)/lib
BINDIR = $(PREFIX)/bin

CC = gcc

CFLAGS = -Wall -pedantic -g

CPPFLAGS =  -I$(INCDIR) 

LDFLAGS = -lm -D_REENTRANT
LDLIBS = -L$(LIBDIR) $(LIBS)  

$(CIBLES): $(OBJS)

.PHONY: all
all: $(CIBLES)


.PHONY: clean
clean:
	rm -f *.o

.PHONY: dep
dep:
	gcc $(CPPFLAGS) -MM $(SRCS)

sudoku.o: sudoku.c
