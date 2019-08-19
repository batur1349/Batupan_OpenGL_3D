#include "../pch.h"
#include "GuiRenderer.hpp"


GuiRenderer::GuiRenderer(Loader& loader)
	: m_quad(CreateQuad(loader))
{
}

void GuiRenderer::Render(const std::vector<GuiTexture>& guis)
{
	m_shader.Start();
	glBindVertexArray(m_quad.GetVaoID());
	glEnableVertexAttribArray(0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);

	for (auto& gui : guis)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, gui.GetTextureId());
		m_shader.LoadTransformationMatrix(Maths::CreateTransformationMatrix(gui.GetPosition(), gui.GetScale()));
		glDrawArrays(GL_TRIANGLE_STRIP, 0, m_quad.GetVertexCount());
	}

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	m_shader.Stop();
}

BaseModel GuiRenderer::CreateQuad(Loader& loader)
{
	std::vector<glm::vec2> vertices;
	vertices.emplace_back(-1, 1);
	vertices.emplace_back(-1, -1);
	vertices.emplace_back(1, 1);
	vertices.emplace_back(1, -1);

	return loader.LoadToVAOGui(vertices);
}
