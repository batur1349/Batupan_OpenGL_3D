#ifndef GUISHADER_HPP
#define GUISHADER_HPP

#include "../Shader/ShaderProgram.hpp"
static const std::string GUI_SHADER_FILE = "Gui/guiShader";

class GuiShader : public ShaderProgram
{
public:
	// Constructor
	GuiShader();

	// Functions
	const void LoadTransformationMatrix(const glm::mat4& matrix);
protected:
	void BindAttributes();
	void GetAllUniformLocations();
private:
	GLuint m_location_transformationMatrix;
};

#endif // !GUISHADER_HPP