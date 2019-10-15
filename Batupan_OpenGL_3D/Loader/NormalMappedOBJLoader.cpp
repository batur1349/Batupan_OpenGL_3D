#include "../pch.h"
#include "NormalMappedOBJLoader.hpp"

BaseModel NormalMappedOBJLoader::LoadOBJ(std::string objFileName, Loader& loader)
{
	std::string fileName = "../Models/" + objFileName + ".obj";
	std::ifstream inFile(fileName, std::ios::in);

	if (!inFile) {
		std::cerr << "NormalMappedObjLoader: File " << fileName << " could not be opened" << std::endl;
		exit(1);
	}

	std::string line;
	std::vector<Vertex*> vertices;
	std::vector<glm::vec2> textures;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> tangents;
	std::vector<GLuint> indices;

	// This loop collects the vertices, texture coords and normals from
	// the obj file.
	while (!inFile.eof()) {
		getline(inFile, line);

		std::istringstream iss(line);
		std::string starts;
		float x, y, z;

		// starts contains e.g. v, vt, tv, s, f
		iss >> starts;

		if (starts == "v") {
			// e.g. v 3.227124 -0.065127 -1.000000
			iss >> x >> y >> z;
			// cout << "got: v " << setprecision(8) << x << " " << y << " " << z << endl;
			glm::vec3 vertex(x, y, z);
			Vertex* newVertex = new Vertex(vertices.size(), vertex);
			vertices.push_back(newVertex);
		}
		else if (starts == "vt") {
			// e.g. vt 0.905299 0.942320
			iss >> x >> y;
			// cout << "got: vt " << setprecision(8) << x << " " << y << endl;
			glm::vec2 texture(x, y);
			textures.push_back(texture);
		}
		else if (starts == "vn") {
			// e.g. vn -1.000000 0.000000 0.000000
			iss >> x >> y >> z;
			// cout << "got: vn " << setprecision(8) << x << " " << y << " " << z << endl;
			glm::vec3 normal(x, y, z);
			normals.push_back(normal);
		}
		else if (starts == "f") {
			// break when faces start
			//cout << "NormalMappedObjLoader: Read " << vertices.size() << " vertices from " << fileName << endl;
			//cout << "NormalMappedObjLoader: Read " << textures.size() << " texture coords from " << fileName << endl;
			//cout << "NormalMappedObjLoader: Read " << normals.size() << " normals from " << fileName << endl;
			break;
		}
	}

	int faces = 0;

	// read the faces in a second loop
	while (!inFile.eof()) {
		if (line == "")
			break;

		std::istringstream iss(line);
		std::string starts;
		int u[9];

		iss >> starts;

		if (starts == "f") {
			// e.g. f 41/1/1 38/2/1 45/3/1
			std::string tmp, f = "";
			iss >> tmp;
			f += tmp + " ";
			iss >> tmp;
			f += tmp + " ";
			iss >> tmp;
			f += tmp;

			// replace /'s with space.
			size_t x = f.find("/");
			while (x < std::string::npos) {
				f.replace(x, 1, " ");
				x = f.find("/", x + 1);
			}
			std::istringstream iss2(f);
			for (int i = 0; i < 9; i++) {
				iss2 >> u[i];
				// the indices in the obj file start from 1, ours start from 0
				u[i]--;
			}

			Vertex* v0 = processVertex(u[0], u[1], u[2], vertices, indices);
			Vertex* v1 = processVertex(u[3], u[4], u[5], vertices, indices);
			Vertex* v2 = processVertex(u[6], u[7], u[8], vertices, indices);
			calculateTangents(v0, v1, v2, textures);

			faces++;
		}

		getline(inFile, line);
	}

	//cout << "NormalMappedObjLoader: Read " << faces << " faces from " << fileName << endl;

	removeUnusedVertices(vertices);
	std::vector<float> verticesArray;
	std::vector<float> texturesArray;
	std::vector<float> normalsArray;
	std::vector<float> tangentsArray;
	float furthest = convertDataToArrays(
		vertices, textures, normals,
		verticesArray, texturesArray, normalsArray, tangentsArray);

	std::vector<int> indicesArray;
	for (int i = 0; i < (int)indices.size(); i++) {
		int u = indices[i];
		indicesArray.push_back(u);
	}

	std::vector<glm::vec2> tex;
	std::vector<glm::vec3> pos, nor, tan;
	furthest = convertDataToVec3Arrays(vertices, textures, normals, pos, tex, nor, tan);

	// free allocated Vertex objects
	for (int i = 0; i < (int)vertices.size(); i++) {
		delete vertices[i];
	}

	return loader.LoadToVAONormal(pos, tex, nor, tan, indicesArray);

	//return loader.LoadToVAONormalMap(verticesArray, texturesArray, normalsArray,
	//	tangentsArray, indicesArray);
}

BaseModel NormalMappedOBJLoader::LoadAssimpOBJ(const std::string& file, Loader& loader)
{
	std::cout << "Loading NormalMap OBJ file " << file << ".obj ..." << "\n";
	// Start timer
	clock_t startTime = clock();

	// Actual importer
	Assimp::Importer importer;

	// Static containers
	std::vector<int> indices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	// Actual path
	std::string path = "../Models/" + file + ".obj";

	const aiScene* scene = importer.ReadFile(path, aiProcess_JoinIdenticalVertices | aiProcess_Triangulate | aiProcess_SortByPType | aiProcess_ConvertToLeftHanded);
	if (!scene)
	{
		fprintf(stderr, importer.GetErrorString());
		getchar();
	}

	const aiMesh* mesh = scene->mMeshes[0];
	// If you want to load more than one mesh than change it with a for loop or etc.
	// In obj files there is only 1 mesh

	// Fill vertices positions
	vertices.reserve(mesh->mNumVertices);
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		aiVector3D pos = mesh->mVertices[i];
		vertices.push_back(glm::vec3(pos.x, pos.y, pos.z));
	}

	// Fill vertices texture coordinates
	uvs.reserve(mesh->mNumVertices);
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		aiVector3D UVW = mesh->mTextureCoords[0][i]; // Assume only 1 set of UV coords; AssImp supports 8 UV sets.
		uvs.push_back(glm::vec2(UVW.x, UVW.y));
	}

	// Fill vertices normals
	normals.reserve(mesh->mNumVertices);
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		aiVector3D n = mesh->mNormals[i];
		normals.push_back(glm::vec3(n.x, n.y, n.z));
	}

	// Fill face indices
	indices.reserve(3 * mesh->mNumFaces);
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		// Assume the model has only triangles.
		indices.push_back(mesh->mFaces[i].mIndices[0]);
		indices.push_back(mesh->mFaces[i].mIndices[1]);
		indices.push_back(mesh->mFaces[i].mIndices[2]);
	}

	// The "scene" pointer will be deleted automatically by "importer"
	std::printf("Load time: %dms\n", clock() - startTime);

	// Return the baseModel
	return loader.LoadToVAO(vertices, uvs, normals, indices);
}

Vertex* NormalMappedOBJLoader::processVertex(int index, int textureIndex, int normalIndex, std::vector<Vertex*>& vertices, std::vector<GLuint>& indices)
{
	Vertex* currentVertex = vertices[index];
	if (!currentVertex->isSet()) {
		currentVertex->setTextureIndex(textureIndex);
		currentVertex->setNormalIndex(normalIndex);
		indices.push_back(index);
		return currentVertex;
	}
	else {
		return dealWithAlreadyProcessedVertex(
			currentVertex, textureIndex, normalIndex, indices, vertices);
	}
}

void NormalMappedOBJLoader::calculateTangents(Vertex* v0, Vertex* v1, Vertex* v2, std::vector<glm::vec2>& textures)
{
	glm::vec3 deltaPos1 = v1->getPosition() - v0->getPosition();
	glm::vec3 deltaPos2 = v2->getPosition() - v0->getPosition();
	glm::vec2 uv0 = textures[v0->getTextureIndex()];
	glm::vec2 uv1 = textures[v1->getTextureIndex()];
	glm::vec2 uv2 = textures[v2->getTextureIndex()];
	glm::vec2 deltaUv1 = uv1 - uv0;
	glm::vec2 deltaUv2 = uv2 - uv0;

	GLfloat r = 1.0f / (deltaUv1.x * deltaUv2.y - deltaUv1.y * deltaUv2.x);
	deltaPos1 *= deltaUv2.y;
	deltaPos2 *= deltaUv1.y;
	glm::vec3 tangent = deltaPos1 - deltaPos2;
	tangent *= r;
	v0->addTangent(tangent);
	v1->addTangent(tangent);
	v2->addTangent(tangent);
}

GLfloat NormalMappedOBJLoader::convertDataToArrays(std::vector<Vertex*>& vertices, std::vector<glm::vec2>& textures, std::vector<glm::vec3>& normals, std::vector<GLfloat>& verticesArray, std::vector<GLfloat>& texturesArray, std::vector<GLfloat>& normalsArray, std::vector<GLfloat>& tangentsArray)
{
	GLfloat furthestPoint = 0;

	for (int i = 0; i < (int)vertices.size(); i++) {
		Vertex* currentVertex = vertices[i];
		if (currentVertex->getLength() > furthestPoint) {
			furthestPoint = currentVertex->getLength();
		}
		glm::vec3 position = currentVertex->getPosition();
		glm::vec2 textureCoord = textures[currentVertex->getTextureIndex()];
		glm::vec3 normalVector = normals[currentVertex->getNormalIndex()];
		glm::vec3 tangent = currentVertex->getAverageTangent();

		verticesArray.push_back(position.x);
		verticesArray.push_back(position.y);
		verticesArray.push_back(position.z);
		texturesArray.push_back(textureCoord.x);
		texturesArray.push_back(1.0 - textureCoord.y);
		normalsArray.push_back(normalVector.x);
		normalsArray.push_back(normalVector.y);
		normalsArray.push_back(normalVector.z);
		tangentsArray.push_back(tangent.x);
		tangentsArray.push_back(tangent.y);
		tangentsArray.push_back(tangent.z);
	}

	return furthestPoint;
}

float NormalMappedOBJLoader::convertDataToVec3Arrays(std::vector<Vertex*>& vertices, std::vector<glm::vec2>& textures, std::vector<glm::vec3>& normals, std::vector<glm::vec3>& verticesArray, std::vector<glm::vec2>& texturesArray, std::vector<glm::vec3>& normalsArray, std::vector<glm::vec3>& tangentsArray)
{
	float furthestPoint = 0;

	for (int i = 0; i < (int)vertices.size(); i++) {
		Vertex* currentVertex = vertices[i];
		if (currentVertex->getLength() > furthestPoint) {
			furthestPoint = currentVertex->getLength();
		}
		glm::vec3 position = currentVertex->getPosition();
		glm::vec2 textureCoord = textures[currentVertex->getTextureIndex()];
		glm::vec3 normalVector = normals[currentVertex->getNormalIndex()];
		glm::vec3 tangent = currentVertex->getAverageTangent();

		verticesArray.push_back(position);
		texturesArray.push_back(glm::vec2(textureCoord.x, 1.0f - textureCoord.y));
		normalsArray.push_back(normalVector);
		tangentsArray.push_back(tangent);
	}

	return furthestPoint;
}

Vertex* NormalMappedOBJLoader::dealWithAlreadyProcessedVertex(Vertex* previousVertex, int newTextureIndex, int newNormalIndex, std::vector<GLuint>& indices, std::vector<Vertex*>& vertices)
{
	if (previousVertex->hasSameTextureAndNormal(newTextureIndex, newNormalIndex)) {
		indices.push_back(previousVertex->getIndex());
		return previousVertex;
	}
	else {
		Vertex* anotherVertex = previousVertex->getDuplicateVertex();
		if (anotherVertex != nullptr) {
			return dealWithAlreadyProcessedVertex(anotherVertex, newTextureIndex, newNormalIndex,
				indices, vertices);
		}
		else {
			Vertex* duplicateVertex = new Vertex(vertices.size(), previousVertex->getPosition());
			duplicateVertex->setTextureIndex(newTextureIndex);
			duplicateVertex->setNormalIndex(newNormalIndex);
			previousVertex->setDuplicateVertex(duplicateVertex);
			vertices.push_back(duplicateVertex);
			indices.push_back(duplicateVertex->getIndex());
			return duplicateVertex;
		}
	}
}

void NormalMappedOBJLoader::removeUnusedVertices(std::vector<Vertex*>& vertices)
{
	for (Vertex* vertex : vertices) {
		// TODO: should be done in an own function
		vertex->averageTangents();
		if (!vertex->isSet()) {
			vertex->setTextureIndex(0);
			vertex->setNormalIndex(0);
		}
	}
}
