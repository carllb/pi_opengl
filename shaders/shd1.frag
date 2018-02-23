#version 330 core


in vec2 texCoord;

layout(location = 0) out vec4 n_color;

uniform sampler2D text_sampler;
uniform sampler2D text_start;
uniform sampler2D pixel_sampler;
uniform int start;


void main() {


	if (start == 1){
		 n_color = texture( text_start, texCoord);
	}else{
			//n_color = texture( text_sampler, texCoord);

	int count = 0;
	for (int i = -1; i <= 1; i++){
		for (int j = -1; j <= 1; j++) {
			if (!(i == 0 && j == 0)){
				if (texture( pixel_sampler, vec2(texCoord.x + i,texCoord.y+j)).y >= 0.5 ){
					count++;
				}
			}
		}
	}

	if ( texture( pixel_sampler, texCoord).y >= 0.5){
		if (count < 2){
			n_color = vec4(0,0,0,1);
		}else if (count > 3){
			n_color = vec4(0,0,0,1);
		}else{
			n_color = vec4(0,1,0,1);
		}
	}else if (count == 3) {
		n_color = vec4(0,1,0,1);
	}
	n_color = texture( pixel_sampler, texCoord );
}


}
