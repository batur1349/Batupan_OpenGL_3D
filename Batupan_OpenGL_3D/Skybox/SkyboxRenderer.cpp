#include "../pch.h"
#include "SkyboxRenderer.hpp"


SkyboxRenderer::SkyboxRenderer(Loader& loader, const glm::mat4& projectionMatrix)
	: _cube(loader.LoadToVAOSkybox(VERTICES, 3))
{
	m_texture = loader.LoadCubeMap(FILE_NAMES);
	m_nightTexture = loader.LoadCubeMap(FILE_NAMES_NIGHT);

	m_shader.Start();
	m_shader.ConnectTextureUnits();
	m_shader.LoadProjectionMatrix(projectionMatrix);
	m_shader.Stop();
}

void SkyboxRenderer::Render(Camera& camera, const glm::vec3& color, const float& dt)
{
	m_shader.Start();
	m_shader.LoadViewMatrix(camera, dt);
	m_shader.LoadFogColor(color);
	glBindVertexArray(_cube.GetVaoID());
	glEnableVertexAttribArray(0);
	//BindTextures(dt);
	glDrawArrays(GL_TRIANGLES, 0, _cube.GetVertexCount());
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	m_shader.Stop();
}

void SkyboxRenderer::BindTextures(const float& dt)
{
	float blendFactor;
	int texture1, texture2;

	m_time += dt * 1000;
	m_time = fmod(m_time, 24000.0f);
	if (m_time >= 0 && m_time < 5000.0f)
	{
		texture1 = m_nightTexture;
		texture2 = m_nightTexture;
		blendFactor = (m_time - 0) / (5000 - 0);
	}
	else if (m_time >= 5000 && m_time < 8000)
	{
		texture1 = m_nightTexture;
		texture2 = m_texture;
		blendFactor = (m_time - 5000) / (8000 - 5000);
	}
	else if (m_time >= 8000 && m_time < 21000)
	{
		texture1 = m_texture;
		texture2 = m_texture;
		blendFactor = (m_time - 8000) / (21000 - 8000);
	}
	else
	{
		texture1 = m_texture;
		texture2 = m_nightTexture;
		blendFactor = (m_time - 21000) / (24000 - 21000);
	}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_nightTexture);
	m_shader.LoadBlendFactor(blendFactor);
}
