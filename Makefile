autonomous_taxi: autonomous_taxi.cpp board.cpp taxi.cpp
	g++ -std=c++14 -g -Wall -o taxi autonomous_taxi.cpp board.cpp taxi.cpp cell.cpp algorithm.cpp

board.o: board.cpp
	g++ -std=c++14 -g -Wall -o board board.cpp

taxi.o: taxi.cpp
	g++ -std=c++14 -g -Wall -o taxi taxi.cpp

cell.o: cell.cpp
	g++ -std=c++14 -g -Wall -o cell cell.cpp

algorithm.o: algorithm.cpp	
	g++ -std=c++14 -g -Wall -o algorithm algorithm.cpp

clean:
	rm -f autonomous_taxi *.o