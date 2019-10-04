CCFLAGS=-std=gnu++98 -pedantic -Wall -Werror -ggdb3
sortLines: sortLines.o
	g++ -o sortLines sortLines.o 

sortLines.o: sortLines.cpp 
	g++ $(CCFLAGS) -c sortLines.cpp
