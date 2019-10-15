#ifndef ENTITYRENDERER_HPP
#define ENTITYRENDERER_HPP

#include "../Model/BaseModel.hpp"
#include "../Model/TexturedModel.hpp"
#include "../Shader/BasicShader.hpp"
#include "../Entity/Entity.hpp"
#include "../Toolbox/Maths.hpp"
#include "Frustum.hpp"

class EntityRenderer
{
public:
	EntityRenderer(BasicShader& shader, const glm::mat4& projectionMatrix);

	void RenderEntities(std::map<TexturedModel, std::vector<Entity>, TextureModelCompare>& entities);
	const void RenderEntities(std::map<TexturedModel, std::vector<Entity>, TextureModelCompare>& entities, Frustum& frustum);
	inline void LoadProjectionMatrix(const glm::mat4& projectionMatrix) { m_shader.LoadProjectionMatrix(projectionMatrix); }
private:
	const void BindTexturedModel(TexturedModel& texturedModel);
	const void UnbindTexturedModel();
	const void RenderEntity(Entity& entity);

	BasicShader& m_shader;
};

#endif // !ENTITYRENDERER_HPP