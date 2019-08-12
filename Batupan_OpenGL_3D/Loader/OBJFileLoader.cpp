#include "../pch.h"
#include "OBJFileLoader.hpp"

std::vector<glm::vec3> OBJFileLoader::m_vertices;
std::vector<glm::vec2> OBJFileLoader::m_uvs;
std::vector<glm::vec3> OBJFileLoader::m_normals;
std::vector<int> OBJFileLoader::m_indices;

BaseModel OBJFileLoader::LoadAssimpObjFile(const std::string& fileName, Loader& loader)
{
	std::cout << "Loading OBJ file " << fileName << ".obj ..." << "\n";
	// Start timer
	clock_t startTime = clock();

	// Actual importer
	static Assimp::Importer importer;

	// Actual path
	const std::string path = "../Models/" + fileName + ".obj";

	const aiScene* scene = importer.ReadFile(path, aiProcess_JoinIdenticalVertices | aiProcess_SortByPType | aiProcess_ConvertToLeftHanded);
	if (!scene)
	{
		fprintf(stderr, importer.GetErrorString());
		getchar();
	}

	const aiMesh* mesh = scene->mMeshes[0];
	// If you want to load more than one mesh than change it with a for loop or etc.
	// In obj files there is only 1 mesh

	// Fill vertices positions
	m_vertices.reserve(mesh->mNumVertices);
	m_uvs.reserve(mesh->mNumVertices);
	m_normals.reserve(mesh->mNumVertices);
	m_indices.reserve(3 * mesh->mNumFaces);

	std::thread verticesThread(&ProcessVertices, std::ref(mesh));
	verticesThread.join();
	std::thread uvsThread(&ProcessUVs, std::ref(mesh));
	uvsThread.join();
	std::thread normalsThread(&ProcessNormals, std::ref(mesh));
	normalsThread.join();
	std::thread facesThread(&ProcessFaces, std::ref(mesh));
	facesThread.join();

	// The "scene" pointer will be deleted automatically by "importer"
	std::printf("Load time: %dms\n", clock() - startTime);

	// Return the baseModel
	return loader.LoadToVAO(m_vertices, m_uvs, m_normals, m_indices);
}

BaseModel OBJFileLoader::LoadObjFile(const std::string& fileName, Loader& loader)
{
	std::cout << "Loading OBJ file " << fileName << ".obj ..." << "\n";
	clock_t startTime = clock();

	FILE* file = std::fopen(("../Models/" + fileName + ".obj").c_str(), "r");
	if (file == NULL)
	{
		std::printf("Impossible to open the file ! Are you in the right path ? \n");
		std::exit(-1);
	}

	std::vector<int> out_indices;
	std::vector<glm::vec3> out_vertices;
	std::vector<glm::vec2> temp_textures, out_textures;
	std::vector<glm::vec3> temp_normals, out_normals;

	// Static variables
	int vertexIndex[3], uvIndex[3], normalIndex[3], vertexPointer, matches, res;
	glm::vec3 vertex, normal; glm::vec2 uv;
	bool checked = false;

	while (1)
	{
		char lineHeader[128];
		// read the first word of the line
		res = std::fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		if (std::strcmp(lineHeader, "v") == 0)
		{
			std::fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			out_vertices.push_back(vertex);
		}
		else if (std::strcmp(lineHeader, "vt") == 0)
		{
			std::fscanf(file, "%f %f\n", &uv.x, &uv.y);
			uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_textures.push_back(uv);
		}
		else if (std::strcmp(lineHeader, "vn") == 0)
		{
			std::fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (std::strcmp(lineHeader, "f") == 0)
		{
			matches = std::fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9 && !checked)
			{
				std::printf("File can't be read by our simple parser :-( Try exporting with other options\n");
				std::fclose(file);
				checked = true;
			}

			if (out_indices.size() == 0)
			{
				out_textures.resize(out_vertices.size(), glm::vec2());
				out_normals.resize(out_vertices.size(), glm::vec3());
			}

			for (int i = 0; i < 3; i++)
			{
				vertexPointer = vertexIndex[i] - 1;
				out_indices.push_back(vertexPointer);

				out_textures.at(vertexPointer) = temp_textures.at(uvIndex[i] - 1);
				out_normals.at(vertexPointer) = temp_normals.at(normalIndex[i] - 1);
			}
		}
	}

	// Close the file
	std::fclose(file);

	// Print the time
	std::printf("Load time: %dms\n", clock() - startTime);

	return loader.LoadToVAO(out_vertices, out_textures, out_normals, out_indices);
}

void OBJFileLoader::ProcessVertices(const aiMesh* mesh)
{
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		aiVector3D pos = mesh->mVertices[i];
		m_vertices.push_back(glm::vec3(pos.x, pos.y, pos.z));
	}
}

void OBJFileLoader::ProcessUVs(const aiMesh* mesh)
{
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		aiVector3D UVW = mesh->mTextureCoords[0][i]; // Assume only 1 set of UV coords; AssImp supports 8 UV sets.
		m_uvs.push_back(glm::vec2(UVW.x, UVW.y));
	}
}

void OBJFileLoader::ProcessNormals(const aiMesh* mesh)
{
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		aiVector3D n = mesh->mNormals[i];
		m_normals.push_back(glm::vec3(n.x, n.y, n.z));
	}
}

void OBJFileLoader::ProcessFaces(const aiMesh* mesh)
{
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		// Assume the model has only triangles.
		m_indices.push_back(mesh->mFaces[i].mIndices[0]);
		m_indices.push_back(mesh->mFaces[i].mIndices[1]);
		m_indices.push_back(mesh->mFaces[i].mIndices[2]);
	}
}
