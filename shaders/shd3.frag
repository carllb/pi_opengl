#version 330 core

precision highp float;

in vec2 texCoord;
layout(location = 0) out vec4 n_color;

uniform sampler2D text_start;
uniform sampler2D pixel_sampler;
uniform int start;
uniform vec2 mouse;



vec4 hsv2rgb(vec4 c){
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return vec4(c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y),c.w);
}



float r = 0.034;

void main() {

		vec2 mouse2 = mouse;
		float d = length(texCoord - mouse2);
		if (start == 1){
			n_color = texture(text_start, texCoord);
			n_color.x = 1.0;
			n_color.y = 0.0;
			//n_color = vec4(texCoord.x,texCoord.y,0,1);

		}else if (d < r){
			if (d > 3*r/4){
				n_color = vec4(0,0,0,1);
			}else{
				vec2 c = texCoord - mouse2;
				float th = atan(c.y,c.x);

				float h = (cos(th + d * 100) + 1)/2;
				float s = (sin(th* 10) + 1)/2;
				float v = (sin(d * 1000) + cos(th * 10) + 2)/4;


				n_color = hsv2rgb(vec4(h,s,v,1));
				//n_color = vec4((cos(th + d * 100) + 1)/2, (cos(th + d * 100) + 1)/2, (cos(th + d * 100) + 1)/2,1);

				/*
				if (th > 0){
					n_color= vec4(1,(cos(d*1000) + 1)/2,0,1);
				}else if (th < -3.14f/2.0f){
					n_color= vec4(1,0,(cos(d*1000) + 1)/2,1);
				}else{
					n_color = vec4(0,0,0,1);
				}
				*/
				/*
					if (length(texCoord - mouse2) < r/2.0f) {
						n_color = vec4(0,0,0,1);
					}else{
						n_color = vec4(1,1,0,1);
					}
				*/
			}
		}else{

				vec2 centerCoord = (texCoord - mouse2);
				vec2 centerCoordNorm = normalize( texCoord - vec2(0.5,0.5) );
				float mag = length(centerCoord);

				float new_mag = mag/0.9;

				vec2 trCoord = centerCoordNorm * new_mag + vec2(0.5,0.5);
					//vec2 trCoord = centerCoordNorm * new_mag + mouse2;

				vec4 myColor = texture(pixel_sampler, trCoord - mouse2);

			//	n_color = vec4(myColor.r - 0.001,myColor.gba);
				n_color = vec4(myColor.r ,myColor.gba);

		}
}
