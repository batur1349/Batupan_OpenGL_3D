#ifndef WATERFRAMEBUFFERS_HPP
#define WATERFRAMEBUFFERS_HPP

class WaterFrameBuffers
{
public:
	WaterFrameBuffers();
	~WaterFrameBuffers();

	void BindReflectionFrameBuffer();
	void BindRefractionFrameBuffer();
	void UnbindCurrentFrameBuffer();

	inline GLuint& GetReflectionTexture() { return m_reflectionTexture; }
	inline GLuint& GetRefractionTexture() { return m_refractionTexture; }
	inline GLuint& GetRefractionDepthTexture() { return m_refractionDepthTexture; }
private:
	void InitialiseReflectionFrameBuffer();
	void InitialiseRefractionFrameBuffer();
	void BindFrameBuffer(const GLuint& frameBuffer, const int& width, const int& height);
	GLuint CreateFrameBuffer();
	GLuint CreateTextureAttachment(const int& width, const int& height);
	GLuint CreateDepthTextureAttachment(const int& width, const int& height);
	GLuint CreateDepthBufferAttachment(const int& width, const int& height);

	int REFLECTION_WIDTH = 320, REFLECTION_HEIGHT = 180;
	int REFRACTION_WIDTH = 1280, REFRACTION_HEIGHT = 720;

	GLuint m_reflectionFrameBuffer, m_reflectionTexture, m_reflectionDepthBuffer;
	GLuint m_refractionFrameBuffer, m_refractionTexture, m_refractionDepthTexture;
};

#endif // !WATERFRAMEBUFFERS_HPP