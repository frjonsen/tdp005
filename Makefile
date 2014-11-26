CXXFLAGS=-Wall -Wextra -Weffc++ -Wold-style-cast -Woverloaded-virtual -fdiagnostics-color=always -std=c++11 -pedantic -Werror -g
SDLFLAGS=-lSDL2
SRCDIR=src
BUILDDIR=build
CC=g++-4.9

all: main.o window.o texture.o surface.o renderer.o rectangle.o
	$(CC) window.o main.o texture.o surface.o renderer.o rectangle.o -o app $(SDLFLAGS)

window.o: window.cc
	$(CC) $(CXXFLAGS) -c window.cc

main.o: main.cc
	$(CC) $(CXXFLAGS) -c main.cc

surface.o: surface.cc
	$(CC) $(CXXFLAGS) -c surface.cc

texture.o: texture.cc	
	$(CC) $(CXXFLAGS) -c texture.cc

renderer.o: renderer.cc
	$(CC) $(CXXFLAGS) -c renderer.cc

clean:
	rm -rf *.o
