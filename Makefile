.PHONY: all clean
CXXFLAGS=-Wall -g

all: ej1 ej2

clean:
	rm -f ej1 ej2

ej1: ./src/ej1.cpp
	g++ $(CXXFLAGS) -o $@ $<

ej2: ./src/ej2.cpp
	g++ $(CXXFLAGS) -o $@ $<