#version 320 es

precision highp float;

in vec2 texCoord;
layout(location = 0) out vec4 n_color;

uniform sampler2D text_start;
uniform sampler2D pixel_sampler;
uniform int start;
uniform vec2 mouse;

float r = 0.004;

void main() {


		if (start == 1){
			n_color = texture(text_start, texCoord);
		}else if (length(texCoord - mouse) < r){
				n_color = vec4(0,1,0,1);

		}else{

				vec2 centerCoord = (texCoord - mouse);
				vec2 centerCoordNorm = normalize( texCoord - vec2(0.5,0.5) );
				float mag = length(centerCoord);

				float new_mag = mag/0.9;

				vec2 trCoord = centerCoordNorm * new_mag + vec2(0.5,0.5);

				vec4 myColor = texture(pixel_sampler, trCoord -  mouse);
				n_color = myColor;
		}
}
