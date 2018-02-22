
#ifndef PLANE_H
#define PLANE_H

#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

class Plane {
public:	
	Plane( GLuint shaderID );
	
	void init();
	
	void draw();

private:
	GLuint sID;
	GLuint vaoID;
	GLuint vboVertID;
	GLuint vboTexCoordID;

			
};

#endif
