#pragma once
#include <glm/glm.hpp>
#include <vector>
#define NOMINMAX 
#include <windows.h>
#include <SFML/Graphics.hpp>

class Algorithms
{
	using collection = std::vector<int>;
private:
	static collection interpolate(int i0, int d0, int i1, int d1, const sf::Vector2u& imgSize);
public:
	static CRITICAL_SECTION mutex;
	static void init();
	static void drawLine(glm::ivec2 firstPoint, glm::ivec2 secondPoint, sf::Image& image);
	static void rasterTriangle(std::vector<glm::vec4>& vertices, sf::Image& image, const sf::Color& color, std::vector<float>& zBuffer, const float z);
};

