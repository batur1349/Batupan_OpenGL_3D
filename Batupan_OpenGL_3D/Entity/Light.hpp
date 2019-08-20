#ifndef LIGHT_HPP
#define LIGHT_HPP

class Light
{
public:
	Light(const glm::vec3& position, const glm::vec3& color);
	Light(const glm::vec3& position, const glm::vec3& color, const glm::vec3& attenuation);

	// Getters
	inline const glm::vec3& GetPosition() const { return m_position; }
	inline const glm::vec3& GetColor() const { return m_color; }
	inline const glm::vec3& GetAttenuation() const { return m_attenuation; }

	// Setters
	inline const void SetColor(const glm::vec3& color);
	inline const void SetPosition(const glm::vec3& position);
	inline const void SetAttenuation(const glm::vec3& attenuation);
private:
	glm::vec3 m_position, m_color, m_attenuation;
};

#endif // !LIGHT_HPP