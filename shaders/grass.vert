#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 vertUV;

out vec2 texCoord;

void main() {
		gl_Position = vec4(position, 0.5, 1 );
		texCoord = vec2(vertUV.x, vertUV.y);
}
