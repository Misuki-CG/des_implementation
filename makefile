all: main

des.o: des.h desMartin.c
	gcc -c -Wall desMartin.c



main: des.o main.c
	gcc -o main -Wall des.o main.c

clean:
	rm *.o main
