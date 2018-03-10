
#ifndef PLANE_H
#define PLANE_H

#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

class Plane {
public:
	Plane( GLuint shaderID, int width, int height, int window_width, int window_height, GLFWwindow* w );
	virtual ~Plane();

	virtual void init();

	virtual void bufferTexCoords( int i );

	virtual void draw();

	virtual void uniformMouse();

	virtual void initTexture();

	int getWidth() {
		return w;
	}

	int getHeight() {
		return h;
	}

	GLuint vboTexCoordID[2];
	GLuint sID;
	GLuint vaoID[2];
	GLuint vboVertID[2];

	GLuint textID[3];
	GLuint texUniformLoc[3];
	GLuint startUniformLoc;

	GLuint frameBufferID[2];

	GLuint mouseUniformLoc;

	// For drawing to the screen
	GLuint passShaderID;

	int start;

	int w;
	int h;

	int window_w;
	int window_h;

	GLFWwindow* window;

private:


	GLuint rboID;
	GLuint startTexUniformLoc;
	GLuint pixelTexUniformLoc;

	//GLuint pboID;

	GLuint passFBShaderID;



};

#endif
