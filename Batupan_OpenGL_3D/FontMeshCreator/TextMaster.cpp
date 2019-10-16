#include "../pch.h"
#include "TextMaster.hpp"
#include "TextMeshData.hpp"

TextMaster m_textMaster;

TextMaster::TextMaster()
{
	m_texts = new std::map<FontType*, std::vector<GUIText*>*>;
}

void TextMaster::Init(Loader* loader)
{
	m_renderer = new FontRenderer();
	m_loader = loader;
}

void TextMaster::LoadText(GUIText* text)
{
	FontType* font = text->GetFont();
	TextMeshData* data = font->LoadText(text);
	GLuint vao = m_loader->LoadToVAOText(data->GetVertexPositions(), data->GetTextureCoords());
	text->SetMeshInfo(vao, data->GetVertexCount());
	std::vector<GUIText*>* textBatch = nullptr;
	std::map<FontType*, std::vector<GUIText*>*>::iterator it = m_texts->find(font);

	if (it == m_texts->end())
	{
		textBatch = new std::vector<GUIText*>;
		m_texts->insert(std::pair<FontType*, std::vector<GUIText*>*>(font, textBatch));
	}
	else {
		textBatch = it->second;
	}
	textBatch->push_back(text);

}

void TextMaster::Render()
{
	m_renderer->Render(m_texts);
}

void TextMaster::RemoveText(GUIText* text)
{
	FontType* font = text->GetFont();

	std::map<FontType*, std::vector<GUIText*>*>::iterator it = m_texts->find(font);

	if (it != m_texts->end())
	{
		std::vector<GUIText*>* textBatch = it->second;
		std::vector<GUIText*>::iterator vit = std::find(textBatch->begin(), textBatch->end(), text);
		if (vit != textBatch->end())
		{
			textBatch->erase(vit);
		}
		if (textBatch->empty())
		{
			m_texts->erase(it);
		}
	}
}

void TextMaster::CleanUp()
{
	m_renderer->CleanUp();
}
