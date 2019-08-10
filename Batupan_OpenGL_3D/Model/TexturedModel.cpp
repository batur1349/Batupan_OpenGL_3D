#include "../pch.h"
#include "TexturedModel.hpp"


TexturedModel::TexturedModel(const BaseModel& model, const ModelTexture& texture)
	: m_baseModel(model), m_texture(texture)
{

}
