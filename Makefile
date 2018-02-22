CC = g++
CFLAGS = -g -Wall -lGLEW -lGLU -lglut -lglfw -lGL

main: main.o shader.o
	$(CC) -o main main.o shader.o $(CFLAGS)

main.o: main.cpp tutorial/shader.hpp
	$(CC) -c -o main.o main.cpp $(CFLAGS)

shader.o: tutorial/shader.cpp tutorial/shader.hpp
	$(CC) -c -o shader.o tutorial/shader.cpp $(CFLAGS)
	
Plane.o: Plane.cpp Plane.h
	$(CC) -c -o Plane.o Plane.cpp $(CFLAGS)

clean:
	rm shader.o main.o main Plane.o
