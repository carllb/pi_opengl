
#ifndef PLANE_H
#define PLANE_H

#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

class Plane {
public:
	Plane( GLuint shaderID, int width, int height );
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
	GLuint screenSID;
	GLuint rboID;
	GLuint screenTexUniformLoc;
	GLuint pixelTexUniformLoc;

	GLuint pboID;

	int start;

	int w;
	int h;

	virtual void initTexture();

};

#endif
