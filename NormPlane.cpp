#include "NormPlane.h"

#include "tutorial/shader.hpp"

#include<iostream>

NormPlane::NormPlane( GLuint shaderID, int width, int height, int window_width, int window_height, GLFWwindow* w ):
  Plane( shaderID, width, height, window_width, window_height, w)
{

}


void NormPlane::uniformMouse(){
  	double xpos, ypos;
  	glfwGetCursorPos(window, &xpos, &ypos);
  	//xpos = rand() % (window_w + 1);
  	//pos = rand() % (window_h + 1);
  	//std::cout <<"x:" << xpos << "y: %f" << ypos << std::endl;
  	glUniform2f(	mouseUniformLoc, xpos/window_w, 1 - ypos/window_h );

  }


void NormPlane::init() {
	static const GLfloat vertData[] = {
		// Left bottom triangle
		-1.0f,  1.0f, //a
		-1.0f, -1.0f, //b
		 1.0f, -1.0f, //c

		 // Right top triangle
		 1.0f, -1.0f, //d
		-1.0f,  1.0f, //e
		 1.0f,  1.0f, //f
	};





	glGenVertexArrays(2, vaoID );
	glGenBuffers( 2, vboVertID );
	glGenBuffers( 2, vboTexCoordID );
	glGenFramebuffers(2, frameBufferID);

	// Enable depth test
	//glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	//glDepthFunc(GL_LESS);

	for ( int i =0; i < 2; i++){

		glBindVertexArray( vaoID[i] );

		glBindBuffer(GL_ARRAY_BUFFER, vboVertID[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof( vertData ), vertData,
			GL_STATIC_DRAW );
		glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, 0);

		bufferTexCoords( i );

	}
	glBindBuffer(GL_ARRAY_BUFFER, 0 );
	//glBindVertexArray(0);

	initTexture();
	/*
	glGenRenderbuffers(1, &rboID);
	glBindRenderbuffer(GL_RENDERBUFFER, rboID);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, w, h);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	*/
	glBindFramebuffer(GL_FRAMEBUFFER,frameBufferID[0]);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
			GL_TEXTURE_2D, textID[0], 0);

	GLenum drawBuffers[1] = {GL_COLOR_ATTACHMENT0};
	glDrawBuffers(1,drawBuffers);

	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID[1]);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
			GL_TEXTURE_2D, textID[1], 0);

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
		std::cerr << "FRAMBUFFER FAILED!" << std::endl;
		exit(-1);
	}

	passShaderID = LoadShaders("shaders/pass.vert","shaders/pass2.frag");

	startUniformLoc = glGetUniformLocation(sID, "start");
	texUniformLoc[1] = glGetUniformLocation(sID, "text_start");
	texUniformLoc[0] = glGetUniformLocation(sID, "pixel_sampler");

	texUniformLoc[2] = glGetUniformLocation(passShaderID,"text_sampler");

	mouseUniformLoc = glGetUniformLocation(sID, "mouse");

}


void NormPlane::bufferTexCoords( int i) {
  static const GLfloat texCoords[] = {
		// Left bottom triangle
		0, 1, //a
		0, 0, //b
		1, 0, //c
		//RiggetHeight()t top triangle
		1, 0, //d
		0, 1, //e
		1, 1  //f
	};


	glBindBuffer(GL_ARRAY_BUFFER, vboTexCoordID[i] );
	glBufferData(GL_ARRAY_BUFFER, sizeof( texCoords ), texCoords,
		GL_STATIC_DRAW );
	glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, 0);
}
