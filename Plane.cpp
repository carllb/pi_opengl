#include "Plane.h"

#include "tutorial/shader.hpp"

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <unistd.h>

Plane::Plane( GLuint shaderID, int width, int height ):
	sID(shaderID), start(1), w(width), h(height)
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
		0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		//Right top triangle
		1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f
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


	glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, 0);

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

	startUniformLoc = glGetUniformLocation(sID, "start");

	screenSID = LoadShaders("shaders/pass.vert", "shaders/pass.frag");
	screenTexUniformLoc = glGetUniformLocation(screenSID,"text_sampler");
	pixelTexUniformLoc = glGetUniformLocation(screenSID,"pixel_sampler");

	glGenBuffersARB(1, &pboID);

}


void Plane::initTexture(){
	unsigned char data[w*h*3];

	srand(time(NULL));

	for ( unsigned int i = 1; i<sizeof(data); i+= 3){
		int o = rand() % 10;
		if (o == 9){
			data[i] = 255;
		}else{
			data[i] = 0;
		}


	}
	/*
	data[0] = 255;
	data[1] = 0;
	data[2] = 0;
*/

	glGenTextures(3, textID );
	glBindTexture(GL_TEXTURE_2D, textID[0]);
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	textUniformLoc[0] = glGetUniformLocation(sID, "text_sampler");

	// start pixle arrangment
	glBindTexture(GL_TEXTURE_2D, textID[1]);
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data );

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	textUniformLoc[1] = glGetUniformLocation(sID, "text_start");


	glBindTexture(GL_TEXTURE_2D, textID[2]);
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, 0 );

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D,0);

//	glViewport(0,0,w,h);
}

void Plane::draw() {


	// For the frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
	glViewport(0,0,w,h);

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram( sID );

	glBindVertexArray(vaoID[0]);

	glUniform1i(textUniformLoc[1], 1);
	glUniform1i(pixelTexUniformLoc, 0);
	glUniform1i(startUniformLoc, start);


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textID[2] );
	glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, pboID);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, w, h,
		GL_RGB, GL_UNSIGNED_BYTE, 0);
	glBufferDataARB(GL_PIXEL_UNPACK_BUFFER_ARB, w*h*3,0,GL_STREAM_DRAW_ARB);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textID[1] );

 //Set the uniform texture sampler to use texture 0


	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glDrawArrays(GL_TRIANGLES, 0, 6);
/*
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//glViewport(0,0,w,h);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// For the screen
	glUseProgram( screenSID );

	glBindVertexArray(vaoID[1]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textID );
	// Set the uniform texture sampler to use texture 0
	glUniform1i(textUniformLoc, 0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glDrawArrays(GL_TRIANGLES, 0, 6);

*/
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0,0,w,h);

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram( screenSID );

	glBindVertexArray(vaoID[1]);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textID[0] );
	// Set the uniform texture sampler to use texture 0
	glUniform1i(screenTexUniformLoc, 0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindBufferARB(GL_PIXEL_PACK_BUFFER_ARB, pboID);
	glNamedFramebufferReadBuffer(frameBufferID,GL_FRONT);

	glReadPixels(0,0,w,h, GL_RGB, GL_UNSIGNED_BYTE, 0);

	glBindTexture(GL_TEXTURE_2D, 0 );
	glDisableVertexAttribArray(0);

	glBindVertexArray(0);

	glUseProgram(0);

	start = 0;
	usleep( 2000000 );
}

Plane::~Plane(){
	glDeleteTextures(2, textID );
	glDeleteBuffers(2, vboTexCoordID);
	glDeleteBuffers(2, vboVertID);
	glDeleteVertexArrays(2, vaoID);
	glDeleteFramebuffers(1, &frameBufferID);
}
