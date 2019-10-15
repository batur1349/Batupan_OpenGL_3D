#ifndef NORMALMAPPINGRENDERER_HPP
#define NORMALMAPPINGRENDERER_HPP

#include "../Model/TexturedModel.hpp"
#include "../Entity/Entity.hpp"
#include "../Entity/Lamp.hpp"
#include "../Entity/Camera.hpp"
#include "../Shader/NormalMappingShader.hpp"

class NormalMappingRenderer
{
public:
	NormalMappingRenderer(const glm::mat4& projection);

	const void RenderEntities(std::map<TexturedModel, std::vector<Entity>, TextureModelCompare>& entities, const glm::vec4& clipPlane, const std::vector<Lamp>& lamps, Camera& camera);
	void PrepareTexturedModel(TexturedModel& model);
	void UnbindTexturedModel();
	void PrepareInstance(Entity& entity);
	void Prepare(const glm::vec4& clipPlane, const std::vector<Lamp>& lamps, Camera& camera);
private:
	NormalMappingShader shader;
};

#endif // !NORMALMAPPINGRENDERER_HPP