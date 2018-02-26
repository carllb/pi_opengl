
#ifndef PLANE_H
#define PLANE_H

#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

class Plane {
public:
	Plane( GLuint shaderID, int width, int height, int window_width, int window_height );
	virtual ~Plane();

	virtual void init();

	virtual void draw();

private:


	GLuint sID;
	GLuint vaoID[2];
	GLuint vboVertID[2];
	GLuint vboTexCoordID[2];

	GLuint textID[3];
	GLuint textUniformLoc[3];
	GLuint startUniformLoc;

	GLuint frameBufferID;
	GLuint rboID;
	GLuint startTexUniformLoc;
	GLuint pixelTexUniformLoc;

	GLuint pboID;

	// For drawing to the screen
	GLuint passShaderID;
	GLuint passTexUniformLoc;

	int start;

	int w;
	int h;

	int window_w;
	int window_h;

	virtual void initTexture();

};

#endif
