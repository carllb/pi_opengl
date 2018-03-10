#version 320 es

precision highp float;

in vec2 texCoord;
layout(location = 0) out vec4 n_color;

uniform sampler2D text_start;
uniform sampler2D pixel_sampler;
uniform int start;
uniform ivec2 mouse;

vec2 normalCoord;

void main() {
  if (start == 1) {
    n_color = vec4(0,0,0,1);
  //}else if ( mouse.x < ivec2(texCoord).x + 4 && mouse.x > ivec2(texCoord).x - 4 &&  mouse.y < ivec2(texCoord).y + 4 && mouse.y > ivec2(texCoord).y - 4 ){
  }else if( length(vec2(mouse)-  texCoord )  < 3.0) {
      n_color = vec4(1,1,1,1);
  }else {
    vec4 myColor = texelFetch(pixel_sampler, ivec2(texCoord),0);

    if (myColor.r < 0.5 ){
      int count = 0;
      for (int i = -1; i <= 1; i++){
        for (int j = -1; j <= 1; j++) {
          if (!(i == 0 && j == 0)){
            vec4 c = texelFetch( pixel_sampler, ivec2(texCoord) + ivec2(i,j),0);
              //if (c.r > 0.5){
                float x = c.g;
                float y = c.b;
                bool bx = false;
                bool by = false;
                if ( i < 0){
                   bx = x > 0.7;
                }else if (i == 0){
                  bx = x > 0.3 && x < 0.5;
                }else{
                  bx = x < 0.3;
                }

                if ( j < 0){
                   by = y > 0.7;
                }else if (i == 0){
                  by = y > 0.3 && y < 0.5;
                }else{
                  by = y < 0.3;
                }

                if ( by && bx){
                  n_color = vec4(c.r,c.g - 0.01, c.b - 0.01, 1);
                }else{
                  n_color = myColor;
                }
              }
            //}
          }
        }
      }else{
        n_color = vec4(0,0,0,1);
      }
    }
}
