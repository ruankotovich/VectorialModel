CC=g++
CF=-std=c++14 -Wall -O2 -lm
SRC_P=src

NAME=vmodel


all: merge clean

merge: parser.o main.o docollection.o document.o
	$(CC) $(CF) -o $(NAME) main.o parser.o docollection.o document.o

main.o: parser.o docollection.o $(SRC_P)/main.cpp
	$(CC) $(CF) -c $(SRC_P)/main.cpp

parser.o: $(SRC_P)/parser.cpp
	$(CC) $(CF) -c $(SRC_P)/parser.cpp

docollection.o: document.o $(SRC_P)/docollection.cpp
	$(CC) $(CF) -c $(SRC_P)/docollection.cpp

document.o: $(SRC_P)/document.cpp
	$(CC) $(CF) -c $(SRC_P)/document.cpp

clean:
	rm -rf *.o

purge: clean
	rm vmodel
