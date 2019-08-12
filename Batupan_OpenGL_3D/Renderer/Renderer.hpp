#ifndef RENDERER_HPP
#define RENDERER_HPP

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

class Renderer
{
public:
	Renderer(BasicShader& shader);
	const void Prepare() const;
	void RenderEntities(std::map<TexturedModel, std::vector<Entity>, TextureModelCompare>& entities);

	inline glm::mat4& GetProjectionMatrix() { return m_projectionMatrix; }
private:
	const void CreateProjectionMatrix();
	const void BindTexturedModel(TexturedModel& texturedModel);
	const void UnbindTexturedModel();
	const void RenderEntity(Entity& entity);

	glm::mat4 m_projectionMatrix;
	BasicShader& m_shader;
	const static float FOV, NEAR_PLANE, FAR_PLANE;
};

#endif // !RENDERER_HPP