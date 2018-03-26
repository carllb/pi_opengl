#include "Plane.h"

#include "tutorial/shader.hpp"

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <unistd.h>

Plane::Plane( GLuint shaderID, int width, int height, int window_width, int window_height, GLFWwindow* w ):
	sID(shaderID), start(1), w(width), h(height), window_w(window_width),
		window_h(window_height), window(w)
{
}



void Plane::init() {
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

	passShaderID = LoadShaders("shaders/pass.vert","shaders/pass.frag");

	startUniformLoc = glGetUniformLocation(sID, "start");
	texUniformLoc[1] = glGetUniformLocation(sID, "text_start");
	texUniformLoc[0] = glGetUniformLocation(sID, "pixel_sampler");

	texUniformLoc[2] = glGetUniformLocation(passShaderID,"text_sampler");

	mouseUniformLoc = glGetUniformLocation(sID, "mouse");

}

void Plane::bufferTexCoords( int i) {
	static const GLint texCoords[] = {
		// Left bottom triangle
		0, h, //a
		0, 0, //b
		w, 0, //c
		//Right top triangle
		w, 0, //d
		0, h, //e
		w, h  //f
	};


	glBindBuffer(GL_ARRAY_BUFFER, vboTexCoordID[i] );
	glBufferData(GL_ARRAY_BUFFER, sizeof( texCoords ), texCoords,
		GL_STATIC_DRAW );
	glVertexAttribPointer(1, 2, GL_INT, false, 0, 0);
}


void Plane::initTexture(){
	unsigned char* data = new unsigned char[w*h*4];

	unsigned int size = w * h * 4;

	srand(time(NULL));

	for ( unsigned int i = 0; i<size; i++ ){
		if (i % 3 == 1){
			data[i] = (rand() % 4) == 0? 255: 0;
		}else{
			data[i] = 0;
		}

	}
	/*
	for ( unsigned int i = 1; i < size; i += 3){
		int r = rand() % 2;
		if (r == 0 ){
			data[i] = 255;
		}
	}
*/
	// Main pixel texture
	glGenTextures(3, textID );
	glBindTexture(GL_TEXTURE_2D, textID[0]);
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, textID[1]);
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


	// start pixle texture
	glBindTexture(GL_TEXTURE_2D, textID[2]);
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data );

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, 0, 0, w, h,
		GL_RGB, GL_UNSIGNED_BYTE, data);

	glBindTexture(GL_TEXTURE_2D,0);
	delete data;
}

void Plane::uniformMouse(){
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	//xpos = rand() % (window_w + 1);
	//pos = rand() % (window_h + 1);
	//std::cout <<"x:" << xpos << "y: %f" << ypos << std::endl;
	glUniform2i(	mouseUniformLoc, xpos, window_h-ypos );
}

void Plane::draw() {


	// This is not drawn to the screen it is drawn to framebuffer 0
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID[0]);
	glViewport(0,0,w,h);

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram( sID );

	glBindVertexArray(vaoID[0]);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glUniform1i(texUniformLoc[0], 0);
	glUniform1i(startUniformLoc, start);

	uniformMouse();

	if (start == 1) {
		glActiveTexture(GL_TEXTURE1);
		glUniform1i(texUniformLoc[1], 1);
		glBindTexture(GL_TEXTURE_2D, textID[2] );
	}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textID[1] );

	glDrawArrays(GL_TRIANGLES, 0, 6);


	// This is drawn to framebuffer 1

	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID[1]);
	glViewport(0,0, w, h);
	glUseProgram( passShaderID );

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(vaoID[0]);

	glBindBuffer(GL_ARRAY_BUFFER, vboVertID[0]);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vboTexCoordID[0]);
	glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 2, GL_INT, false, 0, 0);

	glActiveTexture(GL_TEXTURE0);
	glUniform1i(texUniformLoc[2], 0);
	glBindTexture(GL_TEXTURE_2D, textID[0] );

	glDrawArrays(GL_TRIANGLES, 0, 6);


	// Finaly draw to the screen
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0,0, window_w, window_h);

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(vaoID[0]);
	glUseProgram( passShaderID );


	glEnableVertexAttribArray(0);

	glEnableVertexAttribArray(1);

	glActiveTexture(GL_TEXTURE0);
	glUniform1i(texUniformLoc[2], 0);
	glBindTexture(GL_TEXTURE_2D, textID[0] );

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindTexture(GL_TEXTURE_2D, 0 );

	glUseProgram(0);

	start = 0;
	//usleep( 500000 ); // 500000 * 2 = one sec
}


void Plane::reset(){
	start = 1;
}

Plane::~Plane(){
	glDeleteTextures(2, textID );
	glDeleteBuffers(2, vboTexCoordID);
	glDeleteBuffers(2, vboVertID);

//	glDeleteVertexArrays(2, vaoID);
	glDeleteFramebuffers(2, frameBufferID);
}
