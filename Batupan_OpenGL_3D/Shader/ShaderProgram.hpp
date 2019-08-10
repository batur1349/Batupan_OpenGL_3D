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
private:
	GLuint m_programID, m_vertexShaderID, m_fragmentShaderID;

	static GLuint LoadShader(const std::string& file, const GLenum& typeOfShader);
};

#endif // !SHADERPROGRAM_HPP