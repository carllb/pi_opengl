#version 330 core


in vec2 texCoord;

out vec4 color;

uniform sampler2D text_sampler;


void main() {
	color = texture( text_sampler, texCoord );
	//color = vec4(1.0,0.0,1.0,1.0);
}
