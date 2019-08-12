#include "../pch.h"
#include "MasterRenderer.hpp"


MasterRenderer::MasterRenderer()
	: m_renderer(m_shader)
{

}

void MasterRenderer::Render(Light& light, Camera& camera)
{
	// Prepare the screen
	m_renderer.Prepare();
	// Activate the shader
	m_shader.Start();
	// Load shader parameters
	m_shader.LoadLight(light);
	m_shader.LoadViewMatrix(&camera);

	// RenderEntities all of the entities
	m_renderer.RenderEntities(m_entities);
	// Deactivate shader and clear entities
	m_shader.Stop();
	// Clear the entities batch, for the memory management
	m_entities.clear();
}

void MasterRenderer::ConstructEntity(Entity& entity)
{
	// Get the textured model
	TexturedModel& texturedModel = entity.GetTexturedModel();
	// If the texturedmodel is in the map this will do nothing
	// If it is not in the map it will insert it
	m_entities.insert(std::make_pair(texturedModel, std::vector<Entity>()));
	// Add the entity to the entities list
	m_entities.find(texturedModel)->second.push_back(entity);
}
