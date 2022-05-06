
CC = c++

all:
	$(CC) main.cpp -o doc
	sudo mv doc /usr/bin