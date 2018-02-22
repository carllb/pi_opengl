#include "Plane.h"



Plane::Plane( GLuint shaderID ):
	sID(shaderID) 
{
}

void Plane::init() {
	static const GLfloat vertData[] = {
		// Left bottom triangle
		-1.0f,  1.0f,
		-1.0f, -1.0f,
		 1.0f, -1.0f, 	
		 
		 // Right top triangle
		 1.0f, -1.0f,		 
		-1.0f,  1.0f,		
		 1.0f,  1.0f, 
	};
	
	static const GLfloat texCoords[] = {
		// Left bottom triangle
		0f,0f,0f,1,0f,1.0f,1.0f,
		//Right top triangle
		1.0f,1.0f,0f,1.0f,0f
	};
	
	glGenVertexArrays(1, &vaoID );
	glBindVertexArray( vaoID );
	glGenBuffers( 1, &vboVertID );
	glGenBuffers( 1, &vboTexCoordID );
	
	glBindBuffer(GL_ARRAY_BUFFER, vboVertID);
	glBufferData(GL_ARRAY_BUFFER, sizeof( vertData ), vertData, 
		GL_STATIC_DRAW );
	
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, vboTexCoordID );	
	glBufferData(GL_ARRAY_BUFFER, sizeof( texCoords ), texCoords,
		GL_STATIC_DRAW );
		

	glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0 );
	glBind
  
}

void Plane::draw() {
}
