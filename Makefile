.PHONY: all test

all: bin/monte_carlo

clean:
	rm -rf bin/montecarlo *.o

build/src/main.o: src/main.cpp
	g++ -std=c++17 -Wall -Werror -c -o build/src/main.o src/main.cpp

build/src/point.o: src/point.cpp
	g++ -std=c++17 -Wall -Werror -c -o build/src/point.o src/point.cpp

build/src/monte_carlo.o: src/monte_carlo.cpp
	g++ -std=c++17 -Wall -Werror -c -o build/src/monte_carlo.o src/monte_carlo.cpp

bin/monte_carlo: build/src/main.o build/src/point.o build/src/monte_carlo.o
	g++ -o bin/alphabet build/src/main.o build/src/point.o build/src/monte_carlo.o