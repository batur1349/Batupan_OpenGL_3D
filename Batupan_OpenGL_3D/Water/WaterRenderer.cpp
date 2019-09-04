#include "../pch.h"
#include "WaterRenderer.hpp"


WaterRenderer::WaterRenderer(Loader& loader, WaterShader& shader, const glm::mat4& projectionMatrix, const WaterFrameBuffers& fbos)
	: m_shader(shader), m_quad(SetupVAO(loader)), m_fbos(fbos)
{
	m_shader.Start();
	m_dudvId = loader.LoadTexture2D("waterDUDV");
	m_shader.ConnectTextureUnits();
	m_shader.LoadProjectionMatrix(projectionMatrix);
	m_shader.Stop();
}

void WaterRenderer::Render(const std::vector<WaterTile>& water, Camera& camera, const float& deltaTime)
{
	PrepareRender(camera, deltaTime);

	for (auto& tile : water)
	{
		glm::mat4 modelMatrix = Maths::CreateTransformationMatrix(glm::vec3(tile.GetCenterX(), tile.GetHeight(), tile.GetCenterZ()),
			glm::vec3(0.0f), glm::vec3(tile.GetSize()));
		m_shader.LoadModelMatrix(modelMatrix);
		glDrawArrays(GL_TRIANGLES, 0, m_quad.GetVertexCount());
	}
}

void WaterRenderer::PrepareRender(Camera& camera, const float& deltaTime)
{
	m_shader.Start();
	m_shader.LoadViewMatrix(camera);
	m_moveFactor += WAVE_SPEED * deltaTime;
	if (m_moveFactor >= 1.0f)
	{
		m_moveFactor = 0.0f;
	}
	m_shader.LoadMoveFactor(m_moveFactor);
	glBindVertexArray(m_quad.GetVaoID());
	glEnableVertexAttribArray(0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_fbos.GetReflectionTexture());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_fbos.GetRefractionTexture());
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_dudvId);
}

void WaterRenderer::Unbind()
{
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	m_shader.Stop();
}

BaseModel WaterRenderer::SetupVAO(Loader& loader)
{
	std::vector<glm::vec2> vertices = {
		glm::vec2(-1,-1), glm::vec2(-1, 1),
		glm::vec2(1, -1), glm::vec2(1, -1),
		glm::vec2(-1, 1), glm::vec2(1, 1)
	};

	return loader.LoadToVAOGui(vertices);
}
