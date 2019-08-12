#ifndef MASTERRENDERER_HPP
#define MASTERRENDERER_HPP

#include "../Shader/BasicShader.hpp"
#include "Renderer.hpp"

class MasterRenderer
{
public:
	MasterRenderer();

	void Render(Light& light, Camera& camera);
	void ConstructEntity(Entity& entity);
private:
	BasicShader m_shader;
	Renderer m_renderer;

	std::map<TexturedModel, std::vector<Entity>, TextureModelCompare> m_entities;
};

#endif // !MASTERRENDERER_HPP