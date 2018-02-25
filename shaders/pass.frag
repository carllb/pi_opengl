#version 330 core


in vec2 texCoord;

out vec4 color;

uniform sampler2D text_sampler;


void main() {

  float ng = texelFetch( text_sampler, ivec2(texCoord) + ivec2(-1,0),0).g;
  //color = texelFetch( text_sampler, ivec2(texCoord),0);
  color = texture(text_sampler, texCoord);
  /*
  if (ng > 0.5 || mg > 0.5){
    color = vec4(0,1,0,1);
  }else{
    color = vec4(0,0,0,1);
  }
*/


}
