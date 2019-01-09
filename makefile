main : des.o main.o file.o
	gcc -o main des.o main.o file.o

main.o : main.c des.h file.h
	gcc -o main.o -c main.c -W -Wall 

des.o : des.c 
	gcc -o des.o -c des.c -W -Wall

file.o : file.c 
	gcc -o file.o -c file.c -W -Wall

clean :
	rm -rf *.o