#version 320 es

precision highp float;

in vec2 texCoord;

// may cause problems? this shader is used to draw to the screen and in a f
// framebufer so that is why location = 0 is set. Hopfully this still works
// fine when outputting to the screen.
layout(location = 0) out vec4 color;

uniform sampler2D text_sampler;


void main() {

  //color = texelFetch( text_sampler, ivec2(texCoord),0);
  color = texture(text_sampler, texCoord);
  //color = vec4(1,1,1,1);
  /*
  if (ng > 0.5 || mg > 0.5){
    color = vec4(0,1,0,1);
  }else{
    color = vec4(0,0,0,1);
  }
*/


}
