
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
	GLuint vaoID;
	GLuint vboVertID;
	GLuint vboTexCoordID;
	
	GLuint textID;
	GLuint textUniformLoc;

	int w;
	int h;
	
	virtual void initTexture();
			
};

#endif
