CC=g++
CF=-std=c++14 -Wall -O2
SRC_P=src

NAME=vmodel


all: merge clean

merge: parser.o main.o
	$(CC) $(CF) -o $(NAME) main.o parser.o

main.o: parser.o $(SRC_P)/main.cpp
	$(CC) $(CF) -c $(SRC_P)/main.cpp

parser.o: $(SRC_P)/parser.cpp
	$(CC) $(CF) -c $(SRC_P)/parser.cpp

clean:
	rm -rf *.o

purge: clean
	rm vmodel
