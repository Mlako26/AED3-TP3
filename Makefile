.PHONY: all clean
CXXFLAGS=-Wall -g

all: ej1 ej2 ej3 ej3b

clean:
	rm -f ej1 ej2 ej3 ej3b

ej1: ./src/ej1.cpp
	g++ $(CXXFLAGS) -o $@ $<

ej2: ./src/ej2.cpp
	g++ $(CXXFLAGS) -o $@ $<

ej3: ./src/ej3.cpp
	g++ $(CXXFLAGS) -o $@ $<

ej3b: ./src/ej3b.cpp
	g++ $(CXXFLAGS) -o $@ $<