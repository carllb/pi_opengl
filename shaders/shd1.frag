#version 330 core

precision highp float;

in vec2 texCoord;
layout(location = 0) out vec4 n_color;

uniform sampler2D text_start;
uniform sampler2D pixel_sampler;
uniform int start;
uniform ivec2 mouse;


void main() {


		if (start == 1){
			n_color = texelFetch(text_start, ivec2(texCoord),0);
		}else if( (int(length(vec2(mouse)-  texCoord ))  < 50 && int(length(vec2(mouse)-  texCoord ))  > 48) || (int(length(vec2(mouse)-  texCoord ))  < 20 && int(length(vec2(mouse) - texCoord ))  > 18) ) {
	      n_color = vec4(0,1,0,1);
	//	}else if ( abs(mouse.x -  ivec2(texCoord).x) < 50 || abs(mouse.y - ivec2(texCoord).y) < 50 ){
	//		n_color = vec4(0,1,0,1);
		}else{
			vec4 myColor = texelFetch(pixel_sampler, ivec2(texCoord),0);

			int count = 0;
			for (int i = -1; i <= 1; i++){
				for (int j = -1; j <= 1; j++) {
					if (!(i == 0 && j == 0)){
						if (texelFetch( pixel_sampler, ivec2(texCoord) + ivec2(i,j),0).g >= 0.5 ){
							count++;
						}
					}
				}
			}

			if (myColor.g >= 0.5){
				if (count < 2){
					n_color = vec4(0,0,1,1);
				}else if (count > 3){
					n_color = vec4(1,0,0,1);
				}else{
					n_color = vec4(0,1,0,1);
				}
			}else if(count == 3){
				n_color = vec4(0,1,0,0);
			}else{
				n_color = vec4(0,0,0,1);
			}

		}

}
