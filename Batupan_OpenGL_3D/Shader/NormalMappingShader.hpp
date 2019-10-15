#ifndef NORMALMAPPINGSHADER_HPP
#define NORMALMAPPINGSHADER_HPP

#include "ShaderProgram.hpp"
#include "../Entity/Lamp.hpp"
#include "../Entity/Camera.hpp"
#include "../Toolbox/Maths.hpp"

static const std::string NORMALMAPPING_SHADER_FILE = "Shader/normalMappingShader";

class NormalMappingShader : public ShaderProgram
{
public:
	NormalMappingShader();
	void BindAttributes();
	void GetAllUniformLocations();
	void ConnectTextureUnits();
	void LoadShineVariables(const float& damper, const float& reflectivity);
	void LoadTransformationMatrix(const glm::mat4& matrix);
	void LoadLamps(const std::vector<Lamp>& lamps);
	void LoadProjectionMatrix(const glm::mat4& matrix);
	void LoadViewMatrix(Camera& camera);
	void LoadFakeLightingVariable(const bool& useFakeLighting);
	void LoadSkyColor(const float& r, const float& g, const float& b);
	void LoadNumberOfRows(const int& numberOfRows);
	void LoadTextureOffset(const float& x, const float& y);
	void LoadClipPlane(const glm::vec4& vec);
private:
	static constexpr int MAX_LIGHTS = 4;
	int location_transformationMatrix;
	int location_projectionMatrix;
	int location_viewMatrix;
	int location_lightPosition[MAX_LIGHTS];
	int location_lightColor[MAX_LIGHTS];
	int location_attenuation[MAX_LIGHTS];
	int location_shineDamper;
	int location_reflectivity;
	int location_useFakeLighting;
	int location_skyColor;
	int location_numberOfRows;
	int location_textureOffset;
	int location_clipPlane;
	int location_modelTexture;
	int location_normalMap;
};

#endif // !NORMALMAPPINGSHADER_HPP