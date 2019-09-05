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
uniform sampler2D depthMap;
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

	float near = 0.1f;
	float far = 1000.0f;
	float depth = texture(depthMap, refractionTextureCoords).r;
	float floorDistance = 2.0f * near * far / (far + near - (2.0f * depth - 1.0f) * (far - near));

	depth = gl_FragCoord.z;
	float waterDistance = 2.0f * near * far / (far + near - (2.0f * depth - 1.0f) * (far - near));
	float waterDepth = floorDistance - waterDistance;

	vec2 distortedTexCoords = texture(dudvMap, vec2(textureCoords.x + moveFactor, textureCoords.y)).rg*0.1;
	distortedTexCoords = textureCoords + vec2(distortedTexCoords.x, distortedTexCoords.y+moveFactor);
	vec2 totalDistortion = (texture(dudvMap, distortedTexCoords).rg * 2.0 - 1.0) * waveStrength * clamp(waterDepth / 20.0f, 0.0f, 1.0f);

	refractionTextureCoords += totalDistortion;
	refractionTextureCoords = clamp(refractionTextureCoords, 0.001f, 0.999f);
	reflectionTextureCoords += totalDistortion;
	reflectionTextureCoords.x = clamp(reflectionTextureCoords.x, 0.001f, 0.999f);
	reflectionTextureCoords.y = clamp(reflectionTextureCoords.y, -0.999f, -0.001f);

	vec4 reflectionColor = texture(reflectionTexture, reflectionTextureCoords);
	vec4 refractionColor = texture(refractionTexture, refractionTextureCoords);

	vec4 normalMapColor = texture(normalMap, distortedTexCoords);
	vec3 normal = vec3(normalMapColor.r * 2.0f - 1.0f, normalMapColor.b * 3.0f, normalMapColor.g * 2.0f - 1.0f);
	normal = normalize(normal);

	vec3 viewVector = normalize(toCameraVector);
	float refractiveFactor = dot(viewVector, normal);

	vec3 reflectedLight = reflect(normalize(fromLightVector), normal);
	float specular = max(dot(reflectedLight, viewVector), 0.0f);
	specular = pow(specular, shineDamper);
	vec3 specularHighlights = lightColor * specular * reflectivity * clamp(waterDepth / 5.0f, 0.0f, 1.0f);

	out_Color = mix(reflectionColor, refractionColor, refractiveFactor);
	out_Color = mix(out_Color, vec4(0.0f, 0.3f, 0.5f, 1.0f), 0.2f) + vec4(specularHighlights, 0.0f);
	out_Color.a = clamp(waterDepth / 10.0f, 0.0f, 1.0f);
}