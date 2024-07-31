#version 330 core

in vec3 vertColor;
in vec2 textureCoords;

out vec4 fragmentColor;

uniform sampler2D textureSampler;

void main() {
	//fragmentColor = vec4(vertColor, 1.0);
	float intensity = texture(textureSampler, textureCoords).r;
	float brightness = 5.0;
	vec4 averageLuminance = vec4(0.5, 0.5, 0.5, 1.0);
	float contrast = 1.0;
    fragmentColor = vec4(intensity, intensity, intensity, 1.0);
	//fragmentColor = mix(texColor * brightness, 
   //   mix(averageLuminance, texColor, contrast), 0.5);
	//fragmentColor = texture(textureSampler, textureCoords);
}