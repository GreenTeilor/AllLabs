#pragma once
#include <glm/glm.hpp>
#include <vector>
#define NOMINMAX 
#include <windows.h>
#include <SFML/Graphics.hpp>

class Algorithms
{
	using collection = std::vector<float>;
private:
	static collection interpolate(float i0, float d0, float i1, float d1, const sf::Vector2u& imgSize);
	static glm::vec3 interpolateVectors(const glm::vec3& vec1, const glm::vec3& vec2, const glm::vec3& vec3, const float w1, const float w2, const float w3);
public:
	static CRITICAL_SECTION mutex;
	static void init();
	static void drawLine(glm::ivec2 firstPoint, glm::ivec2 secondPoint, sf::Image& image);
	static void rasterTriangle(std::vector<glm::vec4>& vertices, std::vector<glm::vec3>& worldVertices, std::vector<glm::vec3>& normals, const glm::vec3& cameraPos, 
		sf::Image& image, const glm::vec3& ambientLight, std::vector<float>& zBuffer, const float z, 
		const float diffuseLightStrength, const glm::vec3& diffuseLightColor, const glm::vec3& objectColor, const float specularStrength, const glm::mat4& mvp);
};

