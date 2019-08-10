#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "../Model/BaseModel.hpp"
#include "../Model/TexturedModel.hpp"
#include "../Shader/BasicShader.hpp"
#include "../Entity/Entity.hpp"
#include "../Toolbox/Maths.hpp"

class Renderer
{
public:
	Renderer(BasicShader& shader);
	const void Prepare() const;
	const void Render(Entity& entity, BasicShader& shader) const;
private:
	const void CreateProjectionMatrix();

	glm::mat4 m_projectionMatrix;
	const static float FOV, NEAR_PLANE, FAR_PLANE;
};

#endif // !RENDERER_HPP