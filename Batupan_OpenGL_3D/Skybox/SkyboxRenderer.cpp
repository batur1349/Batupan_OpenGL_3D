#include "../pch.h"
#include "SkyboxRenderer.hpp"


SkyboxRenderer::SkyboxRenderer(Loader& loader, const glm::mat4& projectionMatrix)
	: _cube(loader.LoadToVAOSkybox(VERTICES, 3))
{
	_texture = loader.LoadCubeMap(FILE_NAMES);

	_shader.Start();
	_shader.LoadProjectionMatrix(projectionMatrix);
	_shader.Stop();
}

void SkyboxRenderer::Render(Camera& camera)
{
	_shader.Start();
	_shader.LoadViewMatrix(camera);
	glBindVertexArray(_cube.GetVaoID());
	glEnableVertexAttribArray(0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _texture);
	glDrawArrays(GL_TRIANGLES, 0, _cube.GetVertexCount());
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	_shader.Stop();
}