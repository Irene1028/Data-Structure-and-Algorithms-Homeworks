CFLAGS=-Wall -Werror -std=gnu++11 -pedantic -ggdb3

dedup:dedup.o
	g++ -o dedup dedup.o
dedup.o: dedup.cpp
	g++ $(CFLAGS) -c dedup.cpp
