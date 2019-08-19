#version 330

// INPUTS
in vec2 textureCoords;

// OUTPUTS
out vec4 out_Color;

// UNIFORMS
uniform sampler2D guiTexture;

void main()
{
	out_Color = texture(guiTexture, textureCoords);
}