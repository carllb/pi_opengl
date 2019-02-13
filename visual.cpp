

#include "Plane.h"
#include "tutorial/shader.hpp"

#include <stdio.h>
#include <iostream>
#include <unistd.h>


GLFWwindow* window;
GLuint programID;
Plane* p;
const int wwidth = 1920;
const int wheight = 1080;

#ifndef RESOLUTION
const int width = 1920;
const int height = 1080;
#else
const int width = RESOLUTION_WIDTH;
const int height = RESOLUTION_HEIGHT;
#endif

//const int width = 64;
//const int height = 48;

void initOpenGL(){

	std::cout << width << " " << height << std::endl;

	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n");
		exit(-1);
	}

	//glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

//const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	window = glfwCreateWindow( wwidth, wheight, "Visuals", glfwGetPrimaryMonitor() , NULL);



	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		glfwTerminate();
		exit(-1);
	}
	glfwMakeContextCurrent(window); // Initialize GLEW
	glewExperimental=1; // Needed in core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		exit(-1);
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// These shaders do the "effect"
	programID = LoadShaders("shaders/grass.vert","shaders/grass.frag");
	p = new Plane( programID, width, height, wwidth, wheight, window);

	p->init();
}

void beginRender(){
	do {

		float seconds = 0.005;

		p->draw();

		glfwSwapBuffers(window);
		glfwPollEvents();

		usleep((int)(seconds * 1000000));

	} while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
				glfwWindowShouldClose(window) == 0 );
}


void cleanup(){
	delete p;

	glfwTerminate();
	glDeleteProgram( programID );
}


int main() {

	initOpenGL();
	std::cout << "Done with init!" << std::endl;
	beginRender();
	cleanup();

	return 0;
}
