#ifndef SKYBOXRENDERER_HPP
#define SKYBOXRENDERER_HPP

#include "SkyboxShader.hpp"
#include "../Loader/Loader.hpp"
#include "../Entity/Camera.hpp"

class SkyboxRenderer
{
public:
	// Constructor
	SkyboxRenderer(Loader& loader, const glm::mat4& projectionMatrix);

	// Functions
	void Render(Camera& camera, const glm::vec3& color, const float& dt);
	void BindTextures(const float& dt);
private:
	// Variables
	float SIZE = 500.0f;
	double m_time = 0.0f;
	std::vector<glm::vec3> VERTICES = {
		glm::vec3(-SIZE,  SIZE, -SIZE),
		glm::vec3(-SIZE, -SIZE, -SIZE),
		glm::vec3(SIZE, -SIZE, -SIZE),
		glm::vec3(SIZE, -SIZE, -SIZE),
		glm::vec3(SIZE,  SIZE, -SIZE),
		glm::vec3(-SIZE,  SIZE, -SIZE),

		glm::vec3(-SIZE, -SIZE,  SIZE),
		glm::vec3(-SIZE, -SIZE, -SIZE),
		glm::vec3(-SIZE,  SIZE, -SIZE),
		glm::vec3(-SIZE,  SIZE, -SIZE),
		glm::vec3(-SIZE,  SIZE,  SIZE),
		glm::vec3(-SIZE, -SIZE,  SIZE),

		glm::vec3(SIZE, -SIZE, -SIZE),
		glm::vec3(SIZE, -SIZE,  SIZE),
		glm::vec3(SIZE,  SIZE,  SIZE),
		glm::vec3(SIZE,  SIZE,  SIZE),
		glm::vec3(SIZE,  SIZE, -SIZE),
		glm::vec3(SIZE, -SIZE, -SIZE),

		glm::vec3(-SIZE, -SIZE,  SIZE),
		glm::vec3(-SIZE,  SIZE,  SIZE),
		glm::vec3(SIZE,  SIZE,  SIZE),
		glm::vec3(SIZE,  SIZE,  SIZE),
		glm::vec3(SIZE, -SIZE,  SIZE),
		glm::vec3(-SIZE, -SIZE,  SIZE),

		glm::vec3(-SIZE,  SIZE, -SIZE),
		glm::vec3(SIZE,  SIZE, -SIZE),
		glm::vec3(SIZE,  SIZE,  SIZE),
		glm::vec3(SIZE,  SIZE,  SIZE),
		glm::vec3(-SIZE,  SIZE,  SIZE),
		glm::vec3(-SIZE,  SIZE, -SIZE),

		glm::vec3(-SIZE, -SIZE, -SIZE),
		glm::vec3(-SIZE, -SIZE,  SIZE),
		glm::vec3(SIZE, -SIZE, -SIZE),
		glm::vec3(SIZE, -SIZE, -SIZE),
		glm::vec3(-SIZE, -SIZE,  SIZE),
		glm::vec3(SIZE, -SIZE,  SIZE)
	};

	std::vector<std::string> FILE_NAMES = {
		"right", "left", "top", "bottom", "back", "front"
	};

	std::vector<std::string> FILE_NAMES_NIGHT = {
		"nightRight", "nightLeft", "nightTop", "nightBottom", "nightBack", "nightFront"
	};

	BaseModel _cube;
	GLuint m_texture, m_nightTexture;
	SkyboxShader m_shader;
};

#endif // !SKYBOXRENDERER_HPP