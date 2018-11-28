FILE = E3.c
OUTPUT = monte
CC = gcc
LIBS = -lm -lgsl -lgslcblas
#CFLAGS = -O3


run : $(FILE)
	$(CC) -o $(OUTPUT) $(CFLAGS) $(FILE) $(LIBS)

$(OBJS) : $(FILE)

clean:
	@rm monte

