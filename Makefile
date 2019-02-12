CC = g++
CFLAGS = -g -Wall -lGLEW -lGLU -lglut -lglfw -lGL

all: visual visual64

visual64: visual64.o shader.o Plane.o
	$(CC) -o visual64 visual64.o shader.o Plane.o $(CFLAGS)

visual: visual1920.o shader.o Plane.o
	$(CC) -o visual visual1920.o shader.o Plane.o $(CFLAGS)
	
visual64.o: visual.cpp tutorial/shader.hpp Plane.h resolution64x48.h
	$(CC) -c -o visual64.o visual.cpp $(CFLAGS) -include resolution64x48.h

visual1920.o: visual.cpp tutorial/shader.hpp Plane.h resolution1920x1080.h
	$(CC) -c -o visual1920.o visual.cpp $(CFLAGS) -include resolution1920x1080.h

main: main.o shader.o
	$(CC) -o main main.o shader.o $(CFLAGS)

main.o: main.cpp tutorial/shader.hpp
	$(CC) -c -o main.o main.cpp $(CFLAGS)

shader.o: tutorial/shader.cpp tutorial/shader.hpp
	$(CC) -c -o shader.o tutorial/shader.cpp $(CFLAGS)
	
Plane.o: Plane.cpp Plane.h
	$(CC) -c -o Plane.o Plane.cpp $(CFLAGS)

clean:
	rm -f shader.o main.o main Plane.o visual.o visual
