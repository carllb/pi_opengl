#version 320 es

in vec2 texCoord;

out vec4 color;

uniform sampler2D text_sampler;


void main() {
  int count = 0;
  for (int i = 0; i <= 3; i++){
    for (int j = 0; j <= 3; j++) {
      if (  (i != 1 || j != 1) ){
        if ( texelFetch( text_sampler, ivec2(texCoord) +
          ivec2(i-1,j-1),0).g >= 0.1){
          count++;
        }
      }
    }
  }

  if ( texelFetch( text_sampler, ivec2(texCoord),0).g >= 0.5){
    if (count < 2){
      color = vec4(0,0,1,1);
    }else if (count > 3){
      color = vec4(1,0,1,1);
    }else {
      color = vec4(1,0,0,1);
    }
  }else if (count == 0) {
    color = vec4(1,1,1,1);
  }else {
    color = vec4(0,0,0,1);
  }

  //color = texture( text_sampler, texCoord);
}
