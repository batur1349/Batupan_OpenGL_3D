#include "../pch.h"
#include "WaterFrameBuffers.hpp"


WaterFrameBuffers::WaterFrameBuffers()
{
	InitialiseReflectionFrameBuffer();
	InitialiseRefractionFrameBuffer();
}

WaterFrameBuffers::~WaterFrameBuffers()
{
	glDeleteFramebuffers(1, &m_reflectionFrameBuffer);
	glDeleteTextures(1, &m_reflectionTexture);
	glDeleteRenderbuffers(1, &m_reflectionDepthBuffer);

	glDeleteFramebuffers(1, &m_refractionFrameBuffer);
	glDeleteTextures(1, &m_refractionTexture);
	glDeleteTextures(1, &m_refractionDepthTexture);
}

void WaterFrameBuffers::BindReflectionFrameBuffer()
{
	BindFrameBuffer(m_reflectionFrameBuffer, REFLECTION_WIDTH, REFLECTION_HEIGHT);
}

void WaterFrameBuffers::BindRefractionFrameBuffer()
{
	BindFrameBuffer(m_refractionFrameBuffer, REFRACTION_WIDTH, REFRACTION_HEIGHT);
}

void WaterFrameBuffers::UnbindCurrentFrameBuffer()
{
	int x, y;
	glfwGetWindowSize(glfwGetCurrentContext(), &x, &y);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, x, y);
}

void WaterFrameBuffers::InitialiseReflectionFrameBuffer()
{
	m_reflectionFrameBuffer = CreateFrameBuffer();
	m_reflectionTexture = CreateTextureAttachment(REFLECTION_WIDTH, REFLECTION_HEIGHT);
	m_reflectionDepthBuffer = CreateDepthBufferAttachment(REFLECTION_WIDTH, REFLECTION_HEIGHT);
	UnbindCurrentFrameBuffer();
}

void WaterFrameBuffers::InitialiseRefractionFrameBuffer()
{
	m_refractionFrameBuffer = CreateFrameBuffer();
	m_refractionTexture = CreateTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
	m_refractionDepthTexture = CreateDepthTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
	UnbindCurrentFrameBuffer();
}

void WaterFrameBuffers::BindFrameBuffer(const GLuint& frameBuffer, const int& width, const int& height)
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glViewport(0, 0, width, height);
}

GLuint WaterFrameBuffers::CreateFrameBuffer()
{
	GLuint frameBuffer;
	//generate name for frame buffer
	glGenFramebuffers(1, &frameBuffer);
	//create the framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	//indicate that we will always render to color attachment 0
	glDrawBuffer(GL_COLOR_ATTACHMENT0);

	return frameBuffer;
}

GLuint WaterFrameBuffers::CreateTextureAttachment(const int& width, const int& height)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);

	return texture;
}

GLuint WaterFrameBuffers::CreateDepthTextureAttachment(const int& width, const int& height)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture, 0);

	return texture;
}

GLuint WaterFrameBuffers::CreateDepthBufferAttachment(const int& width, const int& height)
{
	GLuint depthBuffer;

	glGenRenderbuffers(1, &depthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);

	return depthBuffer;
}
