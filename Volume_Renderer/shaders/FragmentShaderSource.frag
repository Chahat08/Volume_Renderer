#version 330 core

in vec3 vertColor;
in vec3 textureCoords;

out vec4 fragmentColor;

uniform sampler3D textureSampler;

void main() {
	//fragmentColor = vec4(vertColor, 1.0);
	float intensity = texture(textureSampler, textureCoords).r;

	float brightness = 6.0;
	vec4 averageLuminance = vec4(0.5, 0.5, 0.5, 1.0);
	float contrast = 1.0;

    vec4 texColor = intensity*vec4(1.0, 1.0, 1.0, 1.0);

	//vec4 finalColor = texColor;
	vec4 finalColor = mix(texColor * brightness, 
      mix(averageLuminance, texColor, contrast), 0.5);
	if(finalColor.a<0.001) discard;
	fragmentColor = finalColor;

	//fragmentColor = texture(textureSampler, textureCoords);
}