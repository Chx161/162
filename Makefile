output: critterMain.o Critter.o Board.o
	g++ critterMain.o Critter.o Board.o -Wall -o output

critterMain.o: critterMain.cpp
	g++  -Wall -c critterMain.cpp

Critter.o: Critter.cpp Critter.hpp
		g++  -Wall -c Critter.cpp

Board.o: Board.cpp Board.hpp
		g++  -Wall -c Board.cpp

clean:
	rm *.o output
