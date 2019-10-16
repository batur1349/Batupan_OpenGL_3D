#ifndef FONTSHADER_HPP
#define FONTSHADER_HPP

#include "ShaderProgram.hpp"

static const std::string FONT_SHADER_FILE = "Shader/fontShader";

class FontShader : public ShaderProgram
{
public:
	FontShader();
	void BindAttributes();
	void GetAllUniformLocations();
	void LoadColor(glm::vec3 color);
	void LoadTranslation(glm::vec2 translation);
private:
	int m_location_color;
	int m_location_translation;
};

#endif // !FONTSHADER_HPP