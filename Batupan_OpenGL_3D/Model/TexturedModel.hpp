#include "BaseModel.hpp"
#include "../Texture/ModelTexture.hpp"
#ifndef TEXTUREDMODEL_HPP
#define TEXTUREDMODEL_HPP

class TexturedModel
{
public:
	TexturedModel(const BaseModel& model, const ModelTexture& texture);

	const BaseModel& GetBaseModel() { return m_baseModel; }
	const ModelTexture& GetModelTexture() { return m_texture; }
private:
	BaseModel m_baseModel;
	ModelTexture m_texture;
};

#endif // !TEXTUREDMODEL_HPP