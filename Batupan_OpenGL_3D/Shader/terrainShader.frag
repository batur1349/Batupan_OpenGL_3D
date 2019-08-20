#version 400 core

in vec2 passedTextureCoords;
in vec3 surfaceNormal;
in vec3 toLightVector[4];
in vec3 toCameraVector;
in float visibility;

out vec4 out_Color;

uniform sampler2D backgroundTexture;
uniform sampler2D rTexture;
uniform sampler2D gTexture;
uniform sampler2D bTexture;
uniform sampler2D blendTexture;

uniform vec3 lightColor[4];
uniform vec3 attenuation[4];
uniform float shineDamper;
uniform float reflectivity;
uniform vec3 skyColor;

void main()
{
	vec4 blendMapColor = texture(blendTexture, passedTextureCoords);
	float backTextureAmount = 1 - (blendMapColor.r + blendMapColor.g + blendMapColor.b);
	vec2 tileCoords = passedTextureCoords * 100.0f;
	vec4 backgroundTextureColor = texture(backgroundTexture, tileCoords) * backTextureAmount;

	vec4 rTextureColor = texture(rTexture, tileCoords) * blendMapColor.r;
	vec4 gTextureColor = texture(gTexture, tileCoords) * blendMapColor.g;
	vec4 bTextureColor = texture(bTexture, tileCoords) * blendMapColor.b;

	vec4 totalColor = backgroundTextureColor + rTextureColor + gTextureColor + bTextureColor;

	vec3 unitNormal = normalize(surfaceNormal);
	vec3 unitVectorToCamera = normalize(toCameraVector);

	vec3 totalDiffuse = vec3(0.0f);
	vec3 totalSpecular = vec3(0.0f);
	for(int i = 0; i < 4; i++)
	{
		float distance = length(toLightVector[i]);
		float attenuationFactor = attenuation[i].x + (attenuation[i].y * distance) + (attenuation[i].z * distance * distance);
		vec3 unitLightVector = normalize(toLightVector[i]);
		float nDot1 = dot(unitNormal, unitLightVector);
		float brightness = max(nDot1, 0.0f);
		vec3 lightDirection = -unitLightVector;
		vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);
		float specularFactor = dot(reflectedLightDirection, unitVectorToCamera);
		specularFactor = max(specularFactor, 0.0f);
		float dampedFactor = pow(specularFactor, shineDamper);
		totalDiffuse = totalDiffuse + (brightness * lightColor[i]) / attenuationFactor;
		totalSpecular = totalSpecular + (dampedFactor * reflectivity * lightColor[i]) / attenuationFactor;
	}
	totalDiffuse = max(totalDiffuse, 0.1f);

	out_Color = vec4(totalDiffuse, 1.0f) * totalColor + vec4(totalSpecular, 1.0f);
	out_Color = mix(vec4(skyColor, 1.0f), out_Color, visibility);
}