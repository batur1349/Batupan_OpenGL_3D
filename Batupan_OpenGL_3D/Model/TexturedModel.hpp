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
	const void SetNormalMap(const int& normalMap) { m_texture.SetNormalMap(normalMap); }
private:
	BaseModel m_baseModel;
	ModelTexture m_texture;
};

struct TextureModelCompare
{
public:
	bool operator() (TexturedModel t1, TexturedModel t2) const
	{
		return ((t1.GetBaseModel().GetVaoID() < t2.GetBaseModel().GetVaoID()) ||
			(t1.GetModelTexture().GetID() < t2.GetModelTexture().GetID()));
	}
};

#endif // !TEXTUREDMODEL_HPP