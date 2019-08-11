#ifndef OBJFILELOADER_HPP
#define OBJFILELOADER_HPP

#include "Loader.hpp"

class OBJFileLoader
{
public:
	static BaseModel LoadAssimpObjFile(const std::string& fileName, Loader& loader);
private:

};

#endif // !OBJFILELOADER_HPP