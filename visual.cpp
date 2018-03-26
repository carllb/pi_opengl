

#include "NormPlane.h"
#include "tutorial/shader.hpp"

#include <stdio.h>
#include <iostream>

GLFWwindow* window;
GLuint programID;
Plane* p;
const int wwidth = 1920;
const int wheight = 1080;

const int width = 1920; //1024;
const int height = 1080; //576;

void initOpenGL(){


	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n");
		exit(-1);
	}

	//glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
//	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // We want OpenGL 2.0 ES
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

//const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	//window = glfwCreateWindow( wwidth, wheight, "Visuals", NULL , NULL);
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


	programID = LoadShaders("shaders/shd1.vert","shaders/shd3.frag");
	//p = new NormPlane( programID, width, height, wwidth, wheight, window);
	p = new NormPlane( programID, width, height, wwidth, wheight, window);

	glfwSwapInterval(1);
	p->init();
}

void beginRender(){
	do {

		p->draw();

		glfwSwapBuffers(window);
		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS){
			p->reset();
		}

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
