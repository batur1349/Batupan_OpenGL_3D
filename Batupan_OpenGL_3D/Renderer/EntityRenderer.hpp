#ifndef ENTITYRENDERER_HPP
#define ENTITYRENDERER_HPP

#include "../Model/BaseModel.hpp"
#include "../Model/TexturedModel.hpp"
#include "../Shader/BasicShader.hpp"
#include "../Entity/Entity.hpp"
#include "../Toolbox/Maths.hpp"

struct TextureModelCompare
{
public:
	bool operator() (TexturedModel t1, TexturedModel t2) const
	{
		return ((t1.GetBaseModel().GetVaoID() < t2.GetBaseModel().GetVaoID()) ||
			(t1.GetModelTexture().GetID() < t2.GetModelTexture().GetID()));
	}
};

class EntityRenderer
{
public:
	EntityRenderer(BasicShader& shader, const glm::mat4& projectionMatrix);
	void RenderEntities(std::map<TexturedModel, std::vector<Entity>, TextureModelCompare>& entities);
private:
	const void BindTexturedModel(TexturedModel& texturedModel);
	const void UnbindTexturedModel();
	const void RenderEntity(Entity& entity);

	BasicShader& m_shader;
};

#endif // !ENTITYRENDERER_HPP