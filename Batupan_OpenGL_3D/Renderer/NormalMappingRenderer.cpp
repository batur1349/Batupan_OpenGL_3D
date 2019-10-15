#include "../pch.h"
#include "NormalMappingRenderer.hpp"
#include "MasterRenderer.hpp"

NormalMappingRenderer::NormalMappingRenderer(const glm::mat4& projection)
{
	shader.Start();
	shader.LoadProjectionMatrix(projection);
	shader.ConnectTextureUnits();
	shader.Stop();
}

const void NormalMappingRenderer::RenderEntities(std::map<TexturedModel, std::vector<Entity>, TextureModelCompare>& entities, const glm::vec4& clipPlane, const std::vector<Lamp>& lamps, Camera& camera)
{
	shader.Start();
	Prepare(clipPlane, lamps, camera);

	// Loop through the mapObjects
	for (auto& mapObject : entities)
	{
		// key.first = TexturedModel, key.second = std::vector<Entity>
		// Bind the texturedModel's texture
		TexturedModel texturedModel = mapObject.first;
		PrepareTexturedModel(texturedModel);
		// RenderEntities all of the entities in the container
		for (Entity& entity : mapObject.second)
			PrepareInstance(entity);
		// Unbind the texturedModel
		UnbindTexturedModel();
	}

	shader.Stop();
}

void NormalMappingRenderer::PrepareTexturedModel(TexturedModel& model)
{
	glBindVertexArray(model.GetBaseModel().GetVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	shader.LoadNumberOfRows(model.GetModelTexture().GetNumberOfRows());
	if (model.GetModelTexture().GetTransparency()) {
		MasterRenderer::DisableCulling();
	}
	shader.LoadFakeLightingVariable(model.GetModelTexture().GetFakeLightning());
	shader.LoadShineVariables(model.GetModelTexture().GetShineDamper(), model.GetModelTexture().GetReflectivity());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, model.GetModelTexture().GetID());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, model.GetModelTexture().GetNormalMap());
}

void NormalMappingRenderer::UnbindTexturedModel()
{
	MasterRenderer::EnableCulling();
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glBindVertexArray(0);
}

void NormalMappingRenderer::PrepareInstance(Entity& entity)
{
	shader.LoadTransformationMatrix(Maths::CreateTransformationMatrix(entity.GetPosition(), entity.GetRotation(), entity.GetScale()));
	shader.LoadTextureOffset(entity.GetTextureXOffset(), entity.GetTextureYOffset());
	// Draw the model
	glDrawElements(GL_TRIANGLES, entity.GetTexturedModel().GetBaseModel().GetVertexCount(), GL_UNSIGNED_INT, 0);
}

void NormalMappingRenderer::Prepare(const glm::vec4& clipPlane, const std::vector<Lamp>& lamps, Camera& camera)
{
	shader.LoadClipPlane(clipPlane);
	shader.LoadSkyColor(MasterRenderer::RED, MasterRenderer::GREEN, MasterRenderer::BLUE);
	shader.LoadLamps(lamps);
	shader.LoadViewMatrix(camera);
	shader.ConnectTextureUnits();
}
