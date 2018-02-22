#include "Plane.h"

#include <stdlib.h>
#include <time.h>
#include <iostream>

Plane::Plane( GLuint shaderID, int width, int height ):
	sID(shaderID), w(width), h(height)
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
		0.0,0.0,0.0,1,0,1.0,1.0,
		//Right top triangle
		1.0,1.0,0,1.0,0.0
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
		

	glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0 );
	glBindVertexArray(0);
	
	initTexture();
  
}


void Plane::initTexture(){
	unsigned char data[w*h*4];
	
	srand(time(NULL));
	
	for ( unsigned int i = 0; i<sizeof(data); i++){
		data[i] = (unsigned char) (rand() % 256 );
	}
	
	glGenTextures(1, &textID );
	glBindTexture(GL_TEXTURE_2D, textID);
	//glPixleStorei(GL_UNPACK_ALIGNMENT, 1);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_BGR, GL_UNSIGNED_BYTE, data );
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	textUniformLoc = glGetUniformLocation(sID, "text_sampler");
}

void Plane::draw() {
	
	glUseProgram( sID );
	
	glBindVertexArray(vaoID);	
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textID );
	// Set the uniform texture sampler to use texture 0
	glUniform1i(textUniformLoc, 0); 
	
	glEnableVertexAttribArray(0);	
	glEnableVertexAttribArray(1);
	
	
	glDrawArrays(GL_TRIANGLES, 0, 6);
	
	glBindTexture(GL_TEXTURE_2D, 0 );
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	
	glUseProgram(0);
	
	
}

Plane::~Plane(){
	glDeleteTextures(1, &textID );
	glDeleteBuffers(1, &vboTexCoordID);
	glDeleteBuffers(1, &vboVertID);
	glDeleteVertexArrays(1, &vaoID);	
}
