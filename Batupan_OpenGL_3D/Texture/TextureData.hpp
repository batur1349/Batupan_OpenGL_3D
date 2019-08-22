#ifndef TEXTUREDATA_HPP
#define TEXTUREDATA_HPP

#include "../pch.h"

class TextureData
{
public:
	TextureData(unsigned char* buffer, int width, int height)
	{
		_buffer = buffer;
		_width = width;
		_height = height;
	}

	~TextureData()
	{
		delete _buffer;
	}

	inline int GetWidth() { return _width; }
	inline int GetHeight() { return _height; }
	unsigned char* GetBuffer() { return _buffer; }
private:
	int _width, _height;
	unsigned char* _buffer;
};

#endif // !TEXTUREDATA_HPP