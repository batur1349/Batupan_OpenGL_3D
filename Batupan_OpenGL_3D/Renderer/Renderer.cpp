#include "../pch.h"
#include "Renderer.hpp"

const float Renderer::FOV = 70.0f;
const float Renderer::NEAR_PLANE = 0.1f;
const float Renderer::FAR_PLANE = 1000.0f;

Renderer::Renderer(BasicShader& shader)
{
	CreateProjectionMatrix();
	shader.Start();
	shader.LoadProjectionMatrix(m_projectionMatrix);
	shader.Stop();
}

const void Renderer::Prepare() const
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.2f, 0.3f, 0.4f, 0.5f);
}

const void Renderer::Render(Entity& entity, BasicShader& shader) const
{
	TexturedModel texturedModel = entity.GetTexturedModel();
	BaseModel baseModel = texturedModel.GetBaseModel();
	ModelTexture modelTexture = texturedModel.GetModelTexture();
	glBindVertexArray(baseModel.GetVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glm::mat4 transformationMatrix = Maths::CreateTransformationMatrix(entity.GetPosition(), entity.GetRotation(), entity.GetScale());
	shader.LoadTransformationMatrix(transformationMatrix);

	shader.LoadShineVariables(modelTexture.GetShineDamper(), modelTexture.GetReflectivity());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, modelTexture.GetID());
	glDrawElements(GL_TRIANGLES, baseModel.GetVertexCount(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

const void Renderer::CreateProjectionMatrix()
{
	int sizeX, sizeY;
	glfwGetWindowSize(glfwGetCurrentContext(), &sizeX, &sizeY);

	GLfloat aspectRatio = (float)((float)sizeX / (float)sizeY);
	GLfloat angle = FOV / 2.0f;
	GLfloat radAngle = glm::radians(angle);
	GLfloat tanAngle = tanf(radAngle);
	GLfloat y_scale = (GLfloat)(1.0f / tanAngle) * aspectRatio;
	GLfloat x_scale = y_scale / aspectRatio;
	GLfloat frustum_length = FAR_PLANE - NEAR_PLANE;

	m_projectionMatrix = glm::mat4(1.0f);

	m_projectionMatrix[0][0] = x_scale;
	m_projectionMatrix[1][1] = y_scale;
	m_projectionMatrix[2][2] = -((FAR_PLANE + NEAR_PLANE) / frustum_length);
	m_projectionMatrix[2][3] = -1;
	m_projectionMatrix[3][2] = -(2 * NEAR_PLANE * FAR_PLANE) / frustum_length;
	m_projectionMatrix[3][3] = 0;
}
