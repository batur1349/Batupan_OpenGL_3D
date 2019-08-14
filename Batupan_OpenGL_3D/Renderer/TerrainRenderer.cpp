#include "../pch.h"
#include "TerrainRenderer.hpp"


TerrainRenderer::TerrainRenderer(TerrainShader& shader, const glm::mat4& projectionMatrix)
	: m_shader(shader)
{
	// Create the projection matrix using GLM and load it into the shader
	m_shader.Start();
	m_shader.LoadProjectionMatrix(projectionMatrix);
	m_shader.ConnectTextureUnits();
	m_shader.Stop();
}

const void TerrainRenderer::Render(std::vector<Terrain>& terrains)
{
	for (auto& terrain : terrains)
	{
		PrepareTerrain(terrain);
		LoadModelMatrix(terrain);
		UnbindTexturedModel();
	}
}

void TerrainRenderer::PrepareTerrain(Terrain& terrain)
{
	// Get the BaseModel from the TexturedModel
	BaseModel model = terrain.GetBaseModel();
	// Bind the models vertex array object id so we can render it
	glBindVertexArray(model.GetVaoID());
	// Enable the attrib arrays 0 - Position, 1 - TextureCoords, 2 - Normals
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	// Load shineDamper and reflectivity from the texture
	BindTextures(terrain);
	m_shader.LoadShineVariables(1, 0);
}

void TerrainRenderer::BindTextures(Terrain& terrain)
{
	TerrainTexturePack texturePack = terrain.GetTexturePack();

	// Activate an OpenGL texture unit and tell it where the texture is
	glActiveTexture(GL_TEXTURE0);
	// Bind the texturedModel's texture
	glBindTexture(GL_TEXTURE_2D, texturePack.GetBackgroundTexture().GetTextureID());
	// Activate an OpenGL texture unit and tell it where the texture is
	glActiveTexture(GL_TEXTURE1);
	// Bind the texturedModel's texture
	glBindTexture(GL_TEXTURE_2D, texturePack.GetRedTexture().GetTextureID());
	// Activate an OpenGL texture unit and tell it where the texture is
	glActiveTexture(GL_TEXTURE2);
	// Bind the texturedModel's texture
	glBindTexture(GL_TEXTURE_2D, texturePack.GetGreenTexture().GetTextureID());
	// Activate an OpenGL texture unit and tell it where the texture is
	glActiveTexture(GL_TEXTURE3);
	// Bind the texturedModel's texture
	glBindTexture(GL_TEXTURE_2D, texturePack.GetBlueTexture().GetTextureID());
	// Activate an OpenGL texture unit and tell it where the texture is
	glActiveTexture(GL_TEXTURE4);
	// Bind the texturedModel's texture
	glBindTexture(GL_TEXTURE_2D, terrain.GetBlendMap().GetTextureID());
}

void TerrainRenderer::UnbindTexturedModel()
{
	// Disable the attrib arrays
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

void TerrainRenderer::LoadModelMatrix(Terrain& terrain)
{
	// Load the transformation matrix into the shader
	m_shader.LoadTransformationMatrix(Maths::CreateTransformationMatrix(glm::vec3(terrain.GetX(), 0.0f, terrain.GetZ())
		, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)));
	// Draw the model
	glDrawElements(GL_TRIANGLES, terrain.GetBaseModel().GetVertexCount(), GL_UNSIGNED_INT, 0);
}
