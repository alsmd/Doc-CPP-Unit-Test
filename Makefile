
CC = c++

all:
	$(CC) main.cpp -o doc
	sudo mv doc /usr/bin
	sudo cp Test.hpp /usr/include/Test.hpp