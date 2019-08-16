#version 400 core

in vec3 position;
in vec2 textureCoords;
in vec3 normal;

out vec2 passedTextureCoords;
out vec3 surfaceNormal;
out vec3 toLightVector;
out vec3 toCameraVector;
out float visibility;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix; 
uniform vec3 lightPosition;

uniform float useFakeLightning;

const float density = 0.0025f;
const float gradient = 1.5f;

void main() 
{
	vec4 worldPosition = transformationMatrix * vec4(position, 1.0f);
	vec4 positionRelativeToCamera = viewMatrix * worldPosition;
	gl_Position = projectionMatrix * positionRelativeToCamera;
	passedTextureCoords = textureCoords;

	vec3 actualNormal = normal;
	if(useFakeLightning > 0.5f)
		actualNormal = vec3(0.0f, 1.0f, 0.0f);

	surfaceNormal = (transformationMatrix * vec4(actualNormal, 0.0f)).xyz;
	toLightVector = lightPosition - worldPosition.xyz;
	toCameraVector = (inverse(viewMatrix) * vec4(0.0f, 0.0f, 0.0f, 1.0f)).xyz - worldPosition.xyz;

	float distance = length(positionRelativeToCamera.xyz);
	visibility = exp(-pow((distance * density), gradient));
	visibility = clamp(visibility, 0.0f, 1.0f);
}