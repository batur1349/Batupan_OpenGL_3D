#include "../pch.h"
#include "Renderer.hpp"


void Renderer::Prepare()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.2f, 0.3f, 0.4f, 0.5f);
}

void Renderer::Render(BaseModel* model)
{
	glBindVertexArray(model->GetVaoID());
	glEnableVertexAttribArray(0);
	glDrawElements(GL_TRIANGLES, model->GetVertexCount(), GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}

void Renderer::Render(TexturedModel* model)
{
	BaseModel tempModel = model->GetBaseModel();
	ModelTexture tempTexture = model->GetModelTexture();
	glBindVertexArray(tempModel.GetVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tempTexture.GetID());
	glDrawElements(GL_TRIANGLES, tempModel.GetVertexCount(), GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindVertexArray(0);
}