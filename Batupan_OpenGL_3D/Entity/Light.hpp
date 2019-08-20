#ifndef LIGHT_HPP
#define LIGHT_HPP

class Light
{
public:
	Light(const glm::vec3& position, const glm::vec3& color);

	// Getters
	inline const glm::vec3& GetPosition() const { return m_position; }
	inline const glm::vec3& GetColor() const { return m_color; }

	// Setters
	inline const void SetColor(const glm::vec3& color);
	inline const void SetPosition(const glm::vec3& position);
private:
	glm::vec3 m_position, m_color;
};

#endif // !LIGHT_HPP