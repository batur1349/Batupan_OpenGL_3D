#version 140

in vec2 pass_textureCoords;

out vec4 out_color;

uniform vec3 color;
uniform sampler2D fontAtlas;

const float width = 0.5f;
const float edge = 0.1f;

// Blury outline 0.4f - 0.5f - Solid outline 0.7f - 0.1f
const float borderWidth = 0.7f;
const float borderEdge = 0.1f;

const vec2 offset = vec2(0.0, 0.0);

const vec3 outlineColor = vec3(1.0f, 0.0f, 0.0f);

// TO-DO : Make uniform these constants

void main(void)
{
	float distance = 1.0f - texture(fontAtlas, pass_textureCoords).a;
	float alpha = 1.0f - smoothstep(width, width + edge, distance);

	float distance2 = 1.0f - texture(fontAtlas, pass_textureCoords + offset).a;
	float outlineAlpha = 1.0f - smoothstep(borderWidth, borderWidth + borderEdge, distance2);

	float overallAlpha = alpha + (1.0f - alpha) * outlineAlpha;
	vec3 overallColor = mix(outlineColor, color, alpha / overallAlpha);

	out_color = vec4(overallColor, overallAlpha);
}