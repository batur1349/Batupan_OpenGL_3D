#ifndef NORMALMAPPEDOBJLOADER_HPP
#define NORMALMAPPEDOBJLOADER_HPP

#include "Vertex.h"
#include "Loader.hpp"

class NormalMappedOBJLoader
{
public:
	static BaseModel LoadOBJ(std::string objFileName, Loader& loader);
	static BaseModel LoadAssimpOBJ(const std::string& file, Loader& loader);
private:
	static Vertex* processVertex(
		int index,
		int textureIndex,
		int normalIndex,
		std::vector<Vertex*>& vertices,
		std::vector<GLuint>& indices);

	static void calculateTangents(
		Vertex* v0, Vertex* v1, Vertex* v2,
		std::vector<glm::vec2>& textures);

	static GLfloat convertDataToArrays(
		std::vector<Vertex*>& vertices,
		std::vector<glm::vec2>& textures,
		std::vector<glm::vec3>& normals,
		std::vector<GLfloat>& verticesArray,
		std::vector<GLfloat>& texturesArray,
		std::vector<GLfloat>& normalsArray,
		std::vector<GLfloat>& tangentsArray
	);

	static float convertDataToVec3Arrays(
		std::vector<Vertex*>& vertices,
		std::vector<glm::vec2>& textures,
		std::vector<glm::vec3>& normals,
		std::vector<glm::vec3>& verticesArray,
		std::vector<glm::vec2>& texturesArray,
		std::vector<glm::vec3>& normalsArray,
		std::vector<glm::vec3>& tangentsArray
	);

	static Vertex* dealWithAlreadyProcessedVertex(
		Vertex* previousVertex,
		int newTextureIndex,
		int newNormalIndex,
		std::vector<GLuint>& indices,
		std::vector<Vertex*>& vertices);

	static void removeUnusedVertices(std::vector<Vertex*>& vertices);
};

#endif // !NORMALMAPPEDOBJLOADER_HPP