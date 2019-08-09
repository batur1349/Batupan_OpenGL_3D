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