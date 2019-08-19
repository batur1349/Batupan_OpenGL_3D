#ifndef GUITEXTURE_HPP
#define GUITEXTURE_HPP

class GuiTexture
{
public:
	GuiTexture(const GLuint& texture, const glm::vec2& position, const glm::vec2& scale);

	// Getters
	inline const GLuint& GetTextureId() const { return m_texture; }
	inline const glm::vec2& GetPosition() const { return m_position; }
	inline const glm::vec2& GetScale() const { return m_scale; }
private:
	GLuint m_texture;
	glm::vec2 m_position, m_scale;
};

#endif // !GUITEXTURE_HPP