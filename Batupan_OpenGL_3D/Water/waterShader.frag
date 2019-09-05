#version 400 core

out vec4 out_Color;

in vec4 clipSpace;
in vec2 textureCoords;
in vec3 toCameraVector;

uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;
uniform sampler2D dudvMap;

uniform float moveFactor;

const float waveStrength = 0.02f;

void main(void) 
{
	vec2 ndc = (clipSpace.xy / clipSpace.w) / 2.0f + 0.5f;
	vec2 refractionTextureCoords = ndc;
	vec2 reflectionTextureCoords = vec2(ndc.x, -ndc.y);

	vec2 distortion1 = (texture(dudvMap, vec2(textureCoords.x + moveFactor, textureCoords.y)).rg * 2.0f - 1.0f) * waveStrength; 
	vec2 distortion2 = (texture(dudvMap, vec2(-textureCoords.x + moveFactor, textureCoords.y + moveFactor)).rg * 2.0f - 1.0f) * waveStrength; 
	vec2 totalDistortion = distortion1 + distortion2;

	refractionTextureCoords += totalDistortion;
	refractionTextureCoords = clamp(refractionTextureCoords, 0.001f, 0.999f);
	reflectionTextureCoords += totalDistortion;
	reflectionTextureCoords.x = clamp(reflectionTextureCoords.x, 0.001f, 0.999f);
	reflectionTextureCoords.y = clamp(reflectionTextureCoords.y, -0.999f, -0.001f);

	vec4 reflectionColor = texture(reflectionTexture, reflectionTextureCoords);
	vec4 refractionColor = texture(refractionTexture, refractionTextureCoords);

	vec3 viewVector = normalize(toCameraVector);
	float refractiveFactor = dot(viewVector, vec3(0.0f, 1.0f, 0.0f));

	out_Color = mix(reflectionColor, refractionColor, refractiveFactor);
	out_Color = mix(out_Color, vec4(0.0f, 0.3f, 0.5f, 1.0f), 0.2f);
}