#version 330 core

in vec3 vertColor;
out vec4 fragmentColor;

void main() {
	fragmentColor = vec4(vertColor, 1.0);
}