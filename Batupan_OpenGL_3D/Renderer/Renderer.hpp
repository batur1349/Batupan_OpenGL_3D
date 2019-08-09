#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "../Model/BaseModel.hpp"

class Renderer
{
public:
	void Prepare();
	void Render(BaseModel* model);
private:

};

#endif // !RENDERER_HPP