#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

class ShaderProgram
{
public:
	ShaderProgram(const std::string& fileName);
	~ShaderProgram();

	inline const void Start() const { glUseProgram(m_programID); }
	inline const void Stop() const { glUseProgram(0); }
protected:
	void BindAttribute(int attribute, const std::string& variableName);
	GLuint GetUniformLocation(const std::string& uniformName);

	virtual void BindAttributes() = 0;
	virtual void GetAllUniformLocations() = 0;

	// GPU Data loaders
	void LoadFloat(GLuint location, const float& value);
	void LoadVector3F(GLuint location, const glm::vec3& vector);
	void LoadBool(GLuint location, const bool& value);
	void LoadMatrix4f(GLuint location, const glm::mat4& matrix, const bool& transpose = false);
	void LoadInt(GLuint location, const int& value);
	void LoadVector2f(GLuint location, const glm::vec2& vector);
	void LoadVector4F(GLuint location, const glm::vec4& vector);
private:
	GLuint m_programID, m_vertexShaderID, m_fragmentShaderID;

	static GLuint LoadShader(const std::string& file, const GLenum& typeOfShader);
};

#endif // !SHADERPROGRAM_HPP