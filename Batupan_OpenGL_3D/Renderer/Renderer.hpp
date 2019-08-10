#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "../Model/BaseModel.hpp"
#include "../Model/TexturedModel.hpp"

class Renderer
{
public:
	void Prepare();
	void Render(BaseModel* model);
	void Render(TexturedModel* model);
private:

};

#endif // !RENDERER_HPP