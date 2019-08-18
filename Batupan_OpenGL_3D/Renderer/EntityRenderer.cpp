#include "../pch.h"
#include "EntityRenderer.hpp"
#include "MasterRenderer.hpp"


EntityRenderer::EntityRenderer(BasicShader& shader, const glm::mat4& projectionMatrix)
	:m_shader(shader)
{
	shader.Start();
	shader.LoadProjectionMatrix(projectionMatrix);
	shader.Stop();
}

void EntityRenderer::RenderEntities(std::map<TexturedModel, std::vector<Entity>, TextureModelCompare>& entities)
{
	// Loop through the mapObjects
	for (auto& mapObject : entities)
	{
		// key.first = TexturedModel, key.second = std::vector<Entity>
		// Bind the texturedModel's texture
		TexturedModel texturedModel = mapObject.first;
		BindTexturedModel(texturedModel);
		// RenderEntities all of the entities in the container
		for (Entity entity : mapObject.second)
			RenderEntity(entity);
		// Unbind the texturedModel
		UnbindTexturedModel();
	}
}

const void EntityRenderer::BindTexturedModel(TexturedModel& texturedModel)
{
	// Get the BaseModel from the TexturedModel
	BaseModel model = texturedModel.GetBaseModel();
	// Bind the models vertex array object id so we can render it
	glBindVertexArray(model.GetVaoID());
	// Enable the attrib arrays 0 - Position, 1 - TextureCoords, 2 - Normals
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	// Load shineDamper and reflectivity from the texture
	ModelTexture texture = texturedModel.GetModelTexture();
	// Load the texture atlas position
	m_shader.LoadNumberOfRows(texture.GetNumberOfRows());
	// Chack if texture has transparency
	if (texture.GetTransparency())
		MasterRenderer::DisableCulling();
	m_shader.LoadFakeLightning(texture.GetFakeLightning());
	m_shader.LoadShineVariables(texture.GetShineDamper(), texture.GetReflectivity());
	// Activate an OpenGL texture unit and tell it where the texture is
	glActiveTexture(GL_TEXTURE0);
	// Bind the texturedModel's texture
	glBindTexture(GL_TEXTURE_2D, texturedModel.GetModelTexture().GetID());
}

const void EntityRenderer::UnbindTexturedModel()
{
	MasterRenderer::EnableCulling();
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

const void EntityRenderer::RenderEntity(Entity& entity)
{
	// Load the transformation matrix into the shader
	m_shader.LoadTransformationMatrix(Maths::CreateTransformationMatrix(entity.GetPosition(), entity.GetRotation(), entity.GetScale()));
	// Load the entity's offset value
	m_shader.LoadOffset(glm::vec2(entity.GetTextureXOffset(), entity.GetTextureYOffset()));
	// Draw the model
	glDrawElements(GL_TRIANGLES, entity.GetTexturedModel().GetBaseModel().GetVertexCount(), GL_UNSIGNED_INT, 0);
}
