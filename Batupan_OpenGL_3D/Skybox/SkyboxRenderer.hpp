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
	void Render(Camera& camera);
private:
	// Variables
	float SIZE = 500.0f;
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

	BaseModel _cube;
	GLuint _texture;
	SkyboxShader _shader;
};

#endif // !SKYBOXRENDERER_HPP