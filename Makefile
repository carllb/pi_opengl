CC = g++
CFLAGS = -g -Wall -lGLEW -lGLU -lglut -lglfw -lGL


visual: visual.o shader.o Plane.o NormPlane.o
	$(CC) -o visual visual.o shader.o Plane.o NormPlane.o $(CFLAGS)

visual.o: visual.cpp tutorial/shader.hpp Plane.h
	$(CC) -c -o visual.o visual.cpp $(CFLAGS)

main: main.o shader.o
	$(CC) -o main main.o shader.o $(CFLAGS)

main.o: main.cpp tutorial/shader.hpp
	$(CC) -c -o main.o main.cpp $(CFLAGS)

shader.o: tutorial/shader.cpp tutorial/shader.hpp
	$(CC) -c -o shader.o tutorial/shader.cpp $(CFLAGS)

Plane.o: Plane.cpp Plane.h
	$(CC) -c -o Plane.o Plane.cpp $(CFLAGS)

NormPlane.o: NormPlane.cpp NormPlane.h Plane.h
	$(CC) -c -o NormPlane.o NormPlane.cpp $(CFLAGS)

clean:
	rm -f shader.o main.o main Plane.o visual.o visual
