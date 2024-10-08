#version 330 core

in vec3 vertColor;
in vec2 textureCoords;

out vec4 fragmentColor;

uniform sampler2D textureSampler;

void main() {
	//fragmentColor = vec4(vertColor, 1.0);
	float intensity = texture(textureSampler, textureCoords).r;

	float brightness = 10.0;
	vec4 averageLuminance = vec4(0.1, 0.1, 0.1, 1.0);
	float contrast = 1.0;

    vec4 texColor = vec4(intensity, intensity, intensity, intensity);

	//vec4 finalColor = texColor;
	vec4 finalColor = mix(texColor * brightness, mix(averageLuminance, texColor, contrast), 0.5);
	if(finalColor.a<0.15) discard;
	fragmentColor = finalColor;

	//fragmentColor = texture(textureSampler, textureCoords);
}