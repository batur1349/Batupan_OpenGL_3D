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
	glDrawArrays(GL_TRIANGLES, 0, model->GetVertexCount());
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}