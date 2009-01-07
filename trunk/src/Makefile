CIBLES = sudoku
SRCS = sudoku.c sudoku.h ordonnanceur.c ordonnanceur.h
LIBS = -lpthread

PREFIX = /usr

OBJS = $(SRCS:.c=.o)
INCDIR = $(PREFIX)/include
LIBDIR = $(PREFIX)/lib
BINDIR = $(PREFIX)/bin

CC = gcc

CFLAGS = -Wall -pedantic -g

CPPFLAGS =  -I$(INCDIR)

LDFLAGS = -lm -pthread
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

sudoku.o: sudoku.c ordonnanceur.c sudoku.h ordonnanceur.h
ordonnanceur.o: sudoku.o ordonnanceur.c ordonnanceur.h
