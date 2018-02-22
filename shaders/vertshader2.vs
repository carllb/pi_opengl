#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in float zoom;
layout(location = 2) in vec3 vertexColor;

out float frag_zoom;
out vec3 fragColor;
uniform mat4 MVP;

void main(){

    gl_Position = MVP * vec4(vertexPosition_modelspace,1);

    frag_zoom = zoom;
    fragColor = vertexColor;

}
