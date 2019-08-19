#ifndef GUIRENDERER_HPP
#define GUIRENDERER_HPP

#include "../Toolbox/Maths.hpp"
#include "../Loader/Loader.hpp"
#include "GuiTexture.hpp"
#include "GuiShader.hpp"

class GuiRenderer
{
public:
	GuiRenderer(Loader& loader);

	void Render(const std::vector<GuiTexture>& guis);
private:
	BaseModel CreateQuad(Loader& loader);
	BaseModel m_quad;
	GuiShader m_shader;
};

#endif // !GUIRENDERER_HPP