#version 400 core

out vec4 out_Color;

in vec4 clipSpace;

uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;

void main(void) 
{
	vec2 ndc = (clipSpace.xy / clipSpace.w) / 2.0f + 0.5f;
	vec2 refractionTextureCoords = ndc;
	vec2 reflectionTextureCoords = vec2(ndc.x, -ndc.y);


	vec4 reflectionColor = texture(reflectionTexture, reflectionTextureCoords);
	vec4 refractionColor = texture(refractionTexture, refractionTextureCoords);

	out_Color = mix(reflectionColor, refractionColor, 0.5f);
}