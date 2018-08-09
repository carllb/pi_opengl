#ifndef NORM_PLANE_H
#define NORM_PLANE_H

#include "Plane.h"

class NormPlane : public Plane {

public:
   NormPlane( GLuint shaderID, int width, int height, int window_width, int window_height, GLFWwindow* w );

   virtual void init();

   virtual void uniformMouse();

   virtual void bufferTexCoords( int i );
private:
  double currX, currY;

};

#endif
