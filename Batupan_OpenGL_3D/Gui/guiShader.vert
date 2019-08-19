#version 330

// INPUTS
in vec2 position;

// OUTPUTS
out vec2 textureCoords;

// UNIFORMS
uniform mat4 transformationMatrix;

void main()
{
	gl_Position = transformationMatrix * vec4(position, -0.1f, 1.0f);
	textureCoords = vec2((position.x + 1.0) / 2.0, 1 - (position.y + 1.0) / 2.0);
}