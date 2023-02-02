CC = gcc -Wall -Wextra

all: reader.o printError.o
	$(CC) reader.o printError.o -o main.app

reader.o: reader.c reader.h
	$(CC) reader.c -c -o reader.o -lpthread

printError.o: printError.c printError.h
	$(CC) printError.c -c -o printError.o

clean:
	rm -f *.o main.app
