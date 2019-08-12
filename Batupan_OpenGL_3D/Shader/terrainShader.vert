#version 400 core

in vec3 position;
in vec2 textureCoords;
in vec3 normal;

out vec2 passedTextureCoords;
out vec3 surfaceNormal;
out vec3 toLightVector;
out vec3 toCameraVector;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix; 
uniform vec3 lightPosition;

void main() 
{
	vec4 worldPosition = transformationMatrix * vec4(position, 1.0f);
	gl_Position = projectionMatrix * viewMatrix * worldPosition;
	passedTextureCoords = textureCoords * 40;

	surfaceNormal = (transformationMatrix * vec4(normal, 0.0f)).xyz;
	toLightVector = lightPosition - worldPosition.xyz;
	toCameraVector = (inverse(viewMatrix) * vec4(0.0f, 0.0f, 0.0f, 1.0f)).xyz - worldPosition.xyz;
}