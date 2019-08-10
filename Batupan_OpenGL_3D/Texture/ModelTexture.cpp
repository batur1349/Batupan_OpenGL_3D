#include "../pch.h"
#include "ModelTexture.hpp"

ModelTexture::ModelTexture(const GLuint& id)
	: m_textureID(id)
{

}

const GLuint& ModelTexture::GetID()
{
	return m_textureID;
}