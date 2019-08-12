#include "../pch.h"
#include "Renderer.hpp"

const float Renderer::FOV = 70.0f;
const float Renderer::NEAR_PLANE = 0.1f;
const float Renderer::FAR_PLANE = 1000.0f;

Renderer::Renderer(BasicShader& shader)
	:m_shader(shader)
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);

	CreateProjectionMatrix();
	shader.Start();
	shader.LoadProjectionMatrix(m_projectionMatrix);
	shader.Stop();
}

const void Renderer::Prepare() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.2f, 0.3f, 0.4f, 0.5f);
}

void Renderer::RenderEntities(std::map<TexturedModel, std::vector<Entity>, TextureModelCompare>& entities)
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

const void Renderer::BindTexturedModel(TexturedModel& texturedModel)
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
	m_shader.LoadShineVariables(texture.GetShineDamper(), texture.GetReflectivity());
	// Activate an OpenGL texture unit and tell it where the texture is
	glActiveTexture(GL_TEXTURE0);
	// Bind the texturedModel's texture
	glBindTexture(GL_TEXTURE_2D, texturedModel.GetModelTexture().GetID());
}

const void Renderer::UnbindTexturedModel()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

const void Renderer::RenderEntity(Entity& entity)
{
	// Load the transformation matrix into the shader
	m_shader.LoadTransformationMatrix(Maths::CreateTransformationMatrix(entity.GetPosition(), entity.GetRotation(), entity.GetScale()));
	// Draw the model
	glDrawElements(GL_TRIANGLES, entity.GetTexturedModel().GetBaseModel().GetVertexCount(), GL_UNSIGNED_INT, 0);
}
