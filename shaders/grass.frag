#version 330 core


in vec2 texCoord;

layout(location = 0) out vec4 n_color;

uniform sampler2D text_start;
uniform sampler2D pixel_sampler;
uniform int start;
uniform ivec2 mouse_loc;

float rate = 0.003;
float water_flow_rate = 1.0 / 8;
float grass_drink_rate = 0.02;

// Green is how much grass is on a pixel
// Blue is water; water => grass
// Red is dude; grass + water => dude

void main() {
		if (start == 1){
			n_color = texelFetch(text_start, ivec2(texCoord),0);
		}else{
			vec4 myColor = texelFetch(pixel_sampler, ivec2(texCoord),0);		
			vec4 originalColor = myColor;

			int count = 0;
			for (int i = -1; i <= 1; i++){
				for (int j = -1; j <= 1; j++) {
					if (!(i == 0 && j == 0) ){
						vec4 neighbor = texelFetch( pixel_sampler, ivec2(texCoord) + ivec2(i,j),0);

						float b_diff = neighbor.b - originalColor.b;						

						// Water
						
						/*
						if (neighbor.b < originalColor.b && originalColor.b > water_flow_rate){
							// neighbor has less water so flow to them		
							myColor.b = myColor.b - water_flow_rate;
						}else if( neighbor.b > originalColor.b && neighbor.b > water_flow_rate){
							// neighbor has more water so flow from them
							myColor.b = myColor.b + water_flow_rate;
						}
						*/

						myColor.b = myColor.b + b_diff * water_flow_rate;
						
						// Grass
						if (originalColor.b >= grass_drink_rate){
							// There is water to feed the grass
							if ( neighbor.g > 0) {
								// if the neighbor has grass and there is water it will spread
								myColor.g = myColor.g + rate;
								myColor.b = myColor.b - grass_drink_rate;
							}
						}else if( myColor.g >= rate ){
							// No water to feed the grass and there is grass that can die
							myColor.g = myColor.g - rate;
						}
						
						if (length(mouse_loc - ivec2(texCoord)) < 10){
							myColor.b = 1;
						}

						// dude
						if (originalColor.r > 0){
							myColor.b += originalColor.r;
							myColor.g -= originalColor.r;
						}
						
					}
				}
			}

			n_color = myColor;
			//n_color = vec4(0.5,-0.1,-0.1,-0.1);
		}

}
