CC         = gcc
CFLAGS     = 
INCLUDES   = ./lib

ex1:
	$(CC) 01-insertion_sort.c -I $(INCLUDES) -o insertion_sort

ex2:
	$(CC) 02-quickselect.c -I $(INCLUDES) -o quickselect

ex3:
	$(CC) 03-strassen.c -I $(INCLUDES) -o strassen

ex4:
	$(CC) 04-tarjan.c -I $(INCLUDES) -o tarjan

ex5:
	$(CC) 05-dijkstra.c -I $(INCLUDES) -o dijkstra

ex6:
	$(CC) 06-heapsort.c -I $(INCLUDES) -o heapsort

all: ex1 ex2 ex3 ex4 ex5 ex6

clean:
	find . -type f -executable -exec rm '{}' \;
