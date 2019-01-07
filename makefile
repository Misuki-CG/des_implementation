main : des.o main.o 
	gcc -o main des.o main.o

main.o : main.c des.h 
	gcc -o main.o -c main.c -W -Wall 

des.o : desFlo.c 
	gcc -o des.o -c desFlo.c -W -Wall 