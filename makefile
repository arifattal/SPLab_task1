all: main.exe

main.exe: encoder.o
	gcc -Wall -o main.exe encoder.o
encoder.o: encoder.c
	gcc -c -Wall -o encoder.o encoder.c
clean:
	rm -f *.o *.exe