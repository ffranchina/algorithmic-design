CC         = gcc
CFLAGS     = 
INCLUDES   = ./lib

ex1:
	$(CC) 01-insertion_sort.c -I $(INCLUDES) -o insertion_sort

all: ex1

clean:
	find . -type f -executable -exec rm '{}' \;
