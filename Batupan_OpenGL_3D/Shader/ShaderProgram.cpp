#include "../pch.h"
#include "ShaderProgram.hpp"


ShaderProgram::ShaderProgram(const std::string& fileName)
{
	// Load shaders from file
	m_vertexShaderID = LoadShader(fileName + ".vert", GL_VERTEX_SHADER);
	m_fragmentShaderID = LoadShader(fileName + ".frag", GL_FRAGMENT_SHADER);

	// Create shader program
	m_programID = glCreateProgram();

	// Attach the shaders to the program
	glAttachShader(m_programID, m_vertexShaderID);
	glAttachShader(m_programID, m_fragmentShaderID);

	// Link the program
	glLinkProgram(m_programID);
	glValidateProgram(m_programID);

	// Check validation status
	GLint status;
	glGetProgramiv(m_programID, GL_VALIDATE_STATUS, &status);
	if (status == GL_FALSE)
	{
		// Get info log length
		GLint infoLogLength;
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLogLength);

		// Get the info log
		GLchar* infoLog = new GLchar[infoLogLength];
		glGetProgramInfoLog(m_programID, infoLogLength, NULL, infoLog);
		printf("ERROR: could not validate program \n%s\n", infoLog);

		// Delete the array
		delete[] infoLog;
	}
}

ShaderProgram::~ShaderProgram()
{
	// Make sure we are not using this shader
	Stop();

	// Detach the shaders from the program
	glDetachShader(m_programID, m_vertexShaderID);
	glDetachShader(m_programID, m_fragmentShaderID);

	// Delete the shaders
	glDeleteShader(m_vertexShaderID);
	glDeleteShader(m_fragmentShaderID);

	// Delete the program
	glDeleteProgram(m_programID);
}

void ShaderProgram::BindAttribute(int attribute, const std::string& variableName)
{
	glBindAttribLocation(m_programID, attribute, variableName.c_str());
}

GLuint ShaderProgram::GetUniformLocation(const std::string& uniformName)
{
	return glGetUniformLocation(m_programID, uniformName.c_str());
}

void ShaderProgram::LoadFloat(GLuint location, const float& value)
{
	glUniform1f(location, value);
}

void ShaderProgram::LoadVector3F(GLuint location, const glm::vec3& vector)
{
	glUniform3f(location, vector.x, vector.y, vector.z);
}

void ShaderProgram::LoadBool(GLuint location, const bool& value)
{
	float toLoad = 0;
	if (value)
		toLoad = 1;

	glUniform1f(location, toLoad);
}

void ShaderProgram::LoadMatrix4f(GLuint location, const glm::mat4& matrix, const bool& transpose)
{
	if (transpose)
		glUniformMatrix4fv(location, 1, GL_TRUE, glm::value_ptr(matrix));
	else
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::LoadInt(GLuint location, const int& value)
{
	glUniform1i(location, value);
}

void ShaderProgram::LoadVector2f(GLuint location, const glm::vec2& vector)
{
	glUniform2f(location, vector.x, vector.y);
}

void ShaderProgram::LoadVector4F(GLuint location, const glm::vec4& vector)
{
	glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
}

GLuint ShaderProgram::LoadShader(const std::string& file, const GLenum& typeOfShader)
{
	// 1. Retrieve the vertex/fragment source code from filePath
	std::string shaderCode;
	std::fstream shaderFile;

	// ensures ifstream objects can throw exceptions:
	shaderFile.exceptions(std::ifstream::badbit);
	try
	{
		// Open files
		shaderFile.open(file.c_str());

		if (!shaderFile.is_open())
			std::cout << "ERROR::SHADER::FILE_COULD_NOT_BE_OPENED! :" << file << std::endl;

		std::stringstream shaderStream;

		// Read file's buffer contents into streams
		shaderStream << shaderFile.rdbuf();

		// close file handlers
		shaderFile.close();

		// Convert stream into string
		shaderCode = shaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ :" << file << std::endl;
	}
	const GLchar* shaderCodeGLchar = shaderCode.c_str();

	// 2. Compile shaders
	GLuint shaderID;
	GLint success;
	GLchar infoLog[512];

	// Vertex Shader
	shaderID = glCreateShader(typeOfShader);
	glShaderSource(shaderID, 1, &shaderCodeGLchar, NULL);
	glCompileShader(shaderID);

	// Print compile errors if any
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
		if (typeOfShader == GL_VERTEX_SHADER)
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		else
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return shaderID;
}