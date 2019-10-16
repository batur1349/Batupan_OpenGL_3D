#include "../pch.h"
#include "FontRenderer.hpp"

FontRenderer::FontRenderer()
{
	m_shader = new FontShader();
}

FontRenderer::~FontRenderer()
{
	delete m_shader;
}

void FontRenderer::Render(std::map<FontType*, std::vector<GUIText*>*>* texts)
{
	std::map<FontType*, std::vector<GUIText*>*>::iterator it;
	Prepare();

	for (it = texts->begin(); it != texts->end(); it++)
	{
		FontType* font = it->first;
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, font->GetTextureAtlas());
		for (GUIText* text : *it->second)
		{
			RenderText(text);
		}
	}

	EndRendering();
}

void FontRenderer::CleanUp()
{
	std::cout << "Font Renderer::Font Shader->CleanUp()" << std::endl;
}

void FontRenderer::Prepare()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	m_shader->Start();
}

void FontRenderer::RenderText(GUIText* text)
{
	glBindVertexArray(text->GetMesh());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	m_shader->LoadColor(text->GetColor());
	m_shader->LoadTranslation(text->GetPosition());
	glDrawArrays(GL_TRIANGLES, 0, text->GetVertexCount());
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindVertexArray(0);
}

void FontRenderer::EndRendering()
{
	m_shader->Stop();
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}