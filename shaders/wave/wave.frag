#version 320 es

precision highp float;

in vec2 texCoord;

// may cause problems? this shader is used to draw to the screen and in a f
// framebufer so that is why location = 0 is set. Hopfully this still works
// fine when outputting to the screen.

layout(location = 0) out vec4 color;

uniform sampler2D text_start;
uniform sampler2D pixel_sampler;
uniform int start;
uniform vec2 mouse;

float speed = 0.001;


void main() {
  
  vec4 color_out;
  mat2 rot;
  mat2 sheer;

  float dist = length(mouse - texCoord)/50.0;

  rot[0] = vec2( cos(dist), -sin(dist) );
  rot[1] = vec2( sin(dist), cos(dist) );

  sheer[0] = vec2( 1.0, dist);
  sheer[1] = vec2( 0.0, 1.0 );

  if (start == 1) {
    color_out = vec4(texture(text_start, texCoord).rgba);
  }
  else
  {
    //color_out = vec4(texture(text_start, texCoord).rgba);

    //color_out = texture(pixel_sampler, texCoord + rot*vec2(speed,speed));

    color_out = texture(pixel_sampler, sheer*texCoord);
  }
  color = color_out;

}
