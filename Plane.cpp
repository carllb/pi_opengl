#include "Plane.h"

#include "tutorial/shader.hpp"

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <unistd.h>

Plane::Plane( GLuint shaderID, int width, int height, int window_width, int window_height ):
	sID(shaderID), start(1), w(width), h(height), window_w(window_width),
		window_h(window_height)
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

	glGenFramebuffers(1, &frameBufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);

	glGenVertexArrays(2, vaoID );
	glGenBuffers( 2, vboVertID );
	glGenBuffers( 2, vboTexCoordID );

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

		glBindBuffer(GL_ARRAY_BUFFER, vboTexCoordID[i] );
		glBufferData(GL_ARRAY_BUFFER, sizeof( texCoords ), texCoords,
			GL_STATIC_DRAW );


	glVertexAttribPointer(1, 2, GL_INT, false, 0, 0);

	}
	glBindBuffer(GL_ARRAY_BUFFER, 0 );
	glBindVertexArray(0);

	initTexture();

	glGenRenderbuffers(1, &rboID);
	glBindRenderbuffer(GL_RENDERBUFFER, rboID);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, w, h);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	//glBindFramebuffer(GL_FRAMEBUFFER,frameBufferID);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
			GL_RENDERBUFFER, rboID);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
			GL_TEXTURE_2D, textID[0], 0);

	GLenum drawBuffers[1] = {GL_COLOR_ATTACHMENT0};
	glDrawBuffers(1,drawBuffers);

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
		std::cerr << "FRAMBUFFER FAILED!" << std::endl;
		exit(-1);
	}

	passShaderID = LoadShaders("shaders/pass.vert","shaders/pass.frag");

	startUniformLoc = glGetUniformLocation(sID, "start");
	startTexUniformLoc = glGetUniformLocation(sID, "text_start");
	pixelTexUniformLoc = glGetUniformLocation(sID, "pixel_sampler");

	passTexUniformLoc = glGetUniformLocation(passShaderID,"text_sampler");
	glGenBuffers(1, &pboID);

}


void Plane::initTexture(){
	unsigned char data[w*h*4];

	srand(time(NULL));

	for ( unsigned int i = 0; i<sizeof(data); i++ ){

		data[i] = 0;

	}

	for ( unsigned int i = 1; i < sizeof(data); i += 3){
		int r = rand() % 2;
		if (r == 0 ){
			data[i] = 255;
		}
	}

	// Main pixel texture
	glGenTextures(2, textID );
	glBindTexture(GL_TEXTURE_2D, textID[0]);
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


	// start pixle texture
	glBindTexture(GL_TEXTURE_2D, textID[1]);
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data );

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, 0, 0, w, h,
		GL_RGB, GL_UNSIGNED_BYTE, data);

	glBindTexture(GL_TEXTURE_2D,0);

}

void Plane::draw() {


	// For the frame buffer but right now the fram buffer is disabled

	// This is not drawn to the screen it is drawn just to be saved into a pixle buffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0,0,w,h);

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram( sID );

	glBindVertexArray(vaoID[0]);

	glUniform1i(pixelTexUniformLoc, 0);
	glUniform1i(startUniformLoc, start);


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textID[0] );
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pboID);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, w, h,
		GL_RGB, GL_UNSIGNED_BYTE, 0);
	glBufferData(GL_PIXEL_UNPACK_BUFFER, w*h*3,0,GL_DYNAMIC_DRAW);


	//if (start == 1) {
		glActiveTexture(GL_TEXTURE1);
		glUniform1i(startTexUniformLoc, 1);
		glBindTexture(GL_TEXTURE_2D, textID[1] );
	//}


	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindBuffer(GL_PIXEL_PACK_BUFFER, pboID);
	//glNamedFramebufferReadBuffer(frameBufferID,GL_FRONT);
	glReadBuffer(GL_COLOR_ATTACHMENT0);

	glReadPixels(0,0,w,h, GL_RGB, GL_UNSIGNED_BYTE, 0);

	// This is where it is drawn to the screen. The viewport is set to be the whole screen


	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0,0,window_w,window_h);

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram( passShaderID );

	glBindVertexArray(vaoID[1]);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glActiveTexture(GL_TEXTURE0);
	glUniform1i(passTexUniformLoc, 0);
	glBindTexture(GL_TEXTURE_2D, textID[0] );
	//glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pboID);
	//glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, w, h,
	//	GL_RGB, GL_UNSIGNED_BYTE, 0);
	//glBufferData(GL_PIXEL_UNPACK_BUFFER, w*h*3,0,GL_DYNAMIC_DRAW);

	// Set the uniform texture sampler to use texture 0


	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	//glBindBufferARB(GL_PIXEL_PACK_BUFFER_ARB, pboID);
  //glNamedFramebufferReadBuffer(frameBufferID,GL_FRONT);

	//glReadPixels(0,0,w,h, GL_RGB, GL_UNSIGNED_BYTE, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindTexture(GL_TEXTURE_2D, 0 );

	glBindVertexArray(0);

	glUseProgram(0);

	start = 0;
	//usleep( 5000000 * 2); // 500000 * 2 = one sec
}

Plane::~Plane(){
	glDeleteTextures(2, textID );
	glDeleteBuffers(2, vboTexCoordID);
	glDeleteBuffers(2, vboVertID);
	glDeleteBuffers(1, &pboID);
	glDeleteVertexArrays(2, vaoID);
	glDeleteFramebuffers(1, &frameBufferID);
}
