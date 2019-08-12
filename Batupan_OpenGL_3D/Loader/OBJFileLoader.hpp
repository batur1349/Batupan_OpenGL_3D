#ifndef OBJFILELOADER_HPP
#define OBJFILELOADER_HPP

#include "Loader.hpp"
#define NUM_THREADS = 4;

class OBJFileLoader
{
public:
	static BaseModel LoadAssimpObjFile(const std::string& fileName, Loader& loader);
	static BaseModel LoadObjFile(const std::string& fileName, Loader& loader);
private:
	void static ProcessVertices(const aiMesh* mesh);
	void static ProcessUVs(const aiMesh* mesh);
	void static ProcessNormals(const aiMesh* mesh);
	void static ProcessFaces(const aiMesh* mesh);

	static std::vector<glm::vec3> m_vertices, m_normals;
	static std::vector<glm::vec2> m_uvs;
	static std::vector<int> m_indices;
};

#endif // !OBJFILELOADER_HPP