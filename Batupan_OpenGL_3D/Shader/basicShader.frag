#version 400 core

in vec2 passedTextureCoords;
in vec3 surfaceNormal;
in vec3 toLightVector;

out vec4 out_Color;

uniform sampler2D textureSampler;
uniform vec3 lightColor;

void main()
{
	vec3 unitNormal = normalize(surfaceNormal);
	vec3 unitLightVector = normalize(toLightVector);

	float nDot1 = dot(unitNormal, unitLightVector);
	float brightness = max(nDot1, 0.0f);
	vec3 diffuseLight = brightness * lightColor;

	out_Color = vec4(diffuseLight, 1.0f) * texture(textureSampler, passedTextureCoords);
}