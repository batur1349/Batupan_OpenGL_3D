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

	void Render(const std::vector<WaterTile>& water, Camera& camera);
private:
	void PrepareRender(Camera& camera);
	void Unbind();
	BaseModel SetupVAO(Loader& loader);

	BaseModel m_quad;
	WaterShader m_shader;
	WaterFrameBuffers m_fbos;
};

#endif // !WATERRENDERER_HPP