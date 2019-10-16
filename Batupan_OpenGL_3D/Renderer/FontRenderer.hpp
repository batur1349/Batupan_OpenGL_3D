#ifndef FONTRENDERER_HPP
#define FONTRENDERER_HPP

#include "../FontMeshCreator/FontType.hpp"
#include "../FontMeshCreator/GUIText.hpp"
#include "../Shader/FontShader.hpp"

class FontRenderer
{
public:
	FontRenderer();
	~FontRenderer();

	void Render(std::map<FontType*, std::vector<GUIText*>*>* texts);
	void CleanUp();
	void Prepare();
	void RenderText(GUIText* text);
	void EndRendering();
private:
	FontShader* m_shader;
};

#endif // !FONTRENDERER_HPP