CC         = gcc
CFLAGS     = 
INCLUDES   = ./lib

ex1:
	$(CC) 01-insertion_sort.c -I $(INCLUDES) -o insertion_sort

ex3:
	$(CC) 03-strassen.c -I $(INCLUDES) -o strassen

all: ex1 ex3

clean:
	find . -type f -executable -exec rm '{}' \;
