#ifndef TEXTMASTER_HPP
#define TEXTMASTER_HPP

#include "../Loader/Loader.hpp"

#include "FontType.hpp"
#include "GUIText.hpp"
#include "../Renderer/FontRenderer.hpp"

class TextMaster
{
public:
	TextMaster();

	void Init(Loader* loader);
	void LoadText(GUIText* text);
	void Render();


	void RemoveText(GUIText* text);
	void CleanUp();
private:
	Loader* m_loader;
	std::map<FontType*, std::vector<GUIText*>*>* m_texts;
	FontRenderer* m_renderer;
};

// global variable
extern TextMaster m_textMaster;

#endif // !TEXTMASTER_HPP