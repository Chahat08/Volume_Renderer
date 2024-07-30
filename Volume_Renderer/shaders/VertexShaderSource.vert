#version 330 core
layout(location=0) in vec3 vertexPosition;
layout(location=1) in vec3 vertexColor;

out vec3 vertColor;

uniform mat4 projection, view, model;

void main(){
	gl_Position = projection*view*model*vec4(vertexPosition,1.0);
	vertColor = vertexColor;
}