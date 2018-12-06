CC = gcc
CFLAGS = -O3 -Wall
LIBS = -lm -lgsl -lgslcblas


OBJECTS = main.o
PROGRAM = main

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -f *.o
	touch *.c

