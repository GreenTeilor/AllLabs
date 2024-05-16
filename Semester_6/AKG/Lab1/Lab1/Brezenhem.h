#pragma once
#include <glm/glm.hpp>
#include <vector>
#define NOMINMAX 
#include <windows.h>
#include <algorithm>
#include "Coordinates.h"
#include <SFML/Graphics.hpp>

class Brezenhem
{
public:
	static CRITICAL_SECTION mutex;
	static void init();
	static void processPoints(glm::ivec2 firstPoint, glm::ivec2 secondPoint, sf::Image& image);
};

