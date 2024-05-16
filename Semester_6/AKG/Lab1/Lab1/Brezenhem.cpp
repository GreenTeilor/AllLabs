#include "Brezenhem.h"
#include <iostream>

CRITICAL_SECTION Brezenhem::mutex{};

void Brezenhem::init()
{
	InitializeCriticalSection(&mutex);
}

void Brezenhem::processPoints(glm::ivec2 firstPoint, glm::ivec2 secondPoint, sf::Image& image) {
	auto imgSize = image.getSize();
	if (firstPoint.x < 0 || firstPoint.x >= imgSize.x || firstPoint.y < 0 || firstPoint.y >= imgSize.y)
		return;
	if (secondPoint.x < 0 || secondPoint.x >= imgSize.x || secondPoint.y < 0 || secondPoint.y >= imgSize.y)
		return;
	int dx = std::max(std::abs(secondPoint.x - firstPoint.x), 1);
	int dy = std::max(std::abs(secondPoint.y - firstPoint.y), 1);
	int sx = (secondPoint.x - firstPoint.x) / dx;
	int sy = (secondPoint.y - firstPoint.y) / dy;
	int err = dx - dy;

		while (firstPoint.x != secondPoint.x || firstPoint.y != secondPoint.y)
		{
			//EnterCriticalSection(&mutex);
			if (firstPoint.x > 0 && firstPoint.x < imgSize.x && firstPoint.y > 0 && firstPoint.y < imgSize.y)
				image.setPixel(firstPoint.x, firstPoint.y, sf::Color::White);
			//LeaveCriticalSection(&mutex);

			int e2 = err << 1;
			if (e2 > -dy)
			{
				err -= dy;
				firstPoint.x += sx;
			}
			if (e2 < dx)
			{
				err += dx;
				firstPoint.y += sy;
			}
		}
}