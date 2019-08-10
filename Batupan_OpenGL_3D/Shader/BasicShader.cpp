#include "../pch.h"
#include "BasicShader.hpp"


BasicShader::BasicShader()
	: ShaderProgram(SHADER_FILE)
{
	BindAttribute(0, "position");
}
