#ifndef WATERRENDERER_HPP
#define WATERRENDERER_HPP

#include "WaterTile.hpp"
#include "WaterShader.hpp"
#include "../Model/BaseModel.hpp"
#include "WaterFrameBuffers.hpp"

class WaterRenderer
{
public:
	WaterRenderer(Loader& loader, WaterShader& shader, const glm::mat4& projectionMatrix, const WaterFrameBuffers& fbos);

	void Render(const std::vector<WaterTile>& water, Camera& camera, const Lamp& lamp, const float& deltaTime);
private:
	void PrepareRender(Camera& camera, const Lamp& lamp, const float& deltaTime);
	void Unbind();
	BaseModel SetupVAO(Loader& loader);

	BaseModel m_quad;
	WaterShader m_shader;
	WaterFrameBuffers m_fbos;
	GLuint m_dudvTexture, m_normalMapTexture;
	float WAVE_SPEED = 0.03f;
	float m_moveFactor = 0.0f;
};

#endif // !WATERRENDERER_HPP