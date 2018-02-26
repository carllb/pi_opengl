#version 320 es

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 vertUV;

out vec2 texCoord;

void main() {
		gl_Position = vec4(position.x ,position.y, 0.5, 1 );
		texCoord  = vertUV;
}
