#version 400 core

out vec4 out_Color;

in vec4 clipSpace;
in vec2 textureCoords;
in vec3 toCameraVector;
in vec3 fromLightVector;

uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;
uniform sampler2D dudvMap;
uniform sampler2D normalMap;
uniform vec3 lightColor;

uniform float moveFactor;

const float waveStrength = 0.02f;
const float shineDamper = 20.0f;
const float reflectivity = 0.6f;

void main(void) 
{
	vec2 ndc = (clipSpace.xy / clipSpace.w) / 2.0f + 0.5f;
	vec2 refractionTextureCoords = ndc;
	vec2 reflectionTextureCoords = vec2(ndc.x, -ndc.y);

	vec2 distortedTexCoords = texture(dudvMap, vec2(textureCoords.x + moveFactor, textureCoords.y)).rg*0.1;
	distortedTexCoords = textureCoords + vec2(distortedTexCoords.x, distortedTexCoords.y+moveFactor);
	vec2 totalDistortion = (texture(dudvMap, distortedTexCoords).rg * 2.0 - 1.0) * waveStrength;

	refractionTextureCoords += totalDistortion;
	refractionTextureCoords = clamp(refractionTextureCoords, 0.001f, 0.999f);
	reflectionTextureCoords += totalDistortion;
	reflectionTextureCoords.x = clamp(reflectionTextureCoords.x, 0.001f, 0.999f);
	reflectionTextureCoords.y = clamp(reflectionTextureCoords.y, -0.999f, -0.001f);

	vec4 reflectionColor = texture(reflectionTexture, reflectionTextureCoords);
	vec4 refractionColor = texture(refractionTexture, refractionTextureCoords);

	vec3 viewVector = normalize(toCameraVector);
	float refractiveFactor = dot(viewVector, vec3(0.0f, 1.0f, 0.0f));

	vec4 normalMapColor = texture(normalMap, distortedTexCoords);
	vec3 normal = vec3(normalMapColor.r * 2.0f - 1.0f, normalMapColor.b, normalMapColor.g * 2.0f - 1.0f);
	normal = normalize(normal);

	vec3 reflectedLight = reflect(normalize(fromLightVector), normal);
	float specular = max(dot(reflectedLight, viewVector), 0.0f);
	specular = pow(specular, shineDamper);
	vec3 specularHighlights = lightColor * specular * reflectivity;

	out_Color = mix(reflectionColor, refractionColor, refractiveFactor);
	out_Color = mix(out_Color, vec4(0.0f, 0.3f, 0.5f, 1.0f), 0.2f) + vec4(specularHighlights, 0.0f);
}