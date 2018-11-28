FILE = E3.c
OUTPUT = monte
CC = gcc
LIBS = -lm -lgsl -lgslcblas
CFLAGS = -O3


monte : $(FILE)
	$(CC) -o $(OUTPUT) $(CFLAGS) $(FILE) $(LIBS)


clean:
	@rm monte


