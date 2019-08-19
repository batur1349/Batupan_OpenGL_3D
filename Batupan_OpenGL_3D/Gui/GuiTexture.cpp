#include "../pch.h"
#include "GuiTexture.hpp"


GuiTexture::GuiTexture(const GLuint& texture, const glm::vec2& position, const glm::vec2& scale)
	: m_texture(texture)
{
	m_position = position;
	m_scale = scale;
}
