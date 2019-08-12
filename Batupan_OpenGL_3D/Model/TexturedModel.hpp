#include "BaseModel.hpp"
#include "../Texture/ModelTexture.hpp"
#ifndef TEXTUREDMODEL_HPP
#define TEXTUREDMODEL_HPP

class TexturedModel
{
public:
	TexturedModel(const BaseModel& model, const ModelTexture& texture);

	inline BaseModel& GetBaseModel() { return m_baseModel; }
	inline ModelTexture& GetModelTexture() { return m_texture; }
	inline float& GetReflectivity() { return m_texture.GetReflectivity(); }
	inline float& GetShineDamper() { return m_texture.GetShineDamper(); }

	const void SetReflectivity(const float& reflectivity) { m_texture.SetReflectivity(reflectivity); }
	const void SetShineDamper(const float& shineDamper) { m_texture.SetShineDamper(shineDamper); }
private:
	BaseModel m_baseModel;
	ModelTexture m_texture;
};

#endif // !TEXTUREDMODEL_HPP