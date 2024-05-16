#include "Algorithms.h"
#include <iostream>
#include <cmath>

CRITICAL_SECTION Algorithms::mutex{};

void Algorithms::init()
{
	InitializeCriticalSection(&mutex);
}

void Algorithms::drawLine(glm::ivec2 firstPoint, glm::ivec2 secondPoint, sf::Image& image) {
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

Algorithms::collection Algorithms::interpolate(int i0, int d0, int i1, int d1, const sf::Vector2u& imgSize) {
	collection values{};
	values.reserve(100);
	float a = (float)(d1 - d0) / (i1 - i0);
	float d = d0;
	for (int i = i0; i < i1; ++i) {
		values.push_back(std::clamp(d, (float)0, (float)(imgSize.x - 1)));
		d += a;
	}
	return values;
}

void Algorithms::rasterTriangle (std::vector<glm::vec4>& vertices, sf::Image& image, const sf::Color& color, std::vector<float>& zBuffer, const float z)
{
	auto imgSize = image.getSize();
	
	if ((vertices.at(0).x < 0 || vertices.at(0).x >= imgSize.x || vertices.at(0).y < 0 || vertices.at(0).y >= imgSize.y)
		&& (vertices.at(1).x < 0 || vertices.at(1).x >= imgSize.x || vertices.at(1).y < 0 || vertices.at(1).y >= imgSize.y)
		&& (vertices.at(2).x < 0 || vertices.at(2).x >= imgSize.x || vertices.at(2).y < 0 || vertices.at(2).y >= imgSize.y))
		return;
	
	//Here just sort in ascending order vertices by y
	if (vertices.at(1).y < vertices.at(0).y) { std::swap(vertices.at(0), vertices.at(1)); }
	if (vertices.at(2).y < vertices.at(0).y) { std::swap(vertices.at(2), vertices.at(0)); }
	if (vertices.at(2).y < vertices.at(1).y) { std::swap(vertices.at(2), vertices.at(1)); }

	//Get x coordinates of each triangle side
	collection x01 = interpolate(vertices.at(0).y, vertices.at(0).x, vertices.at(1).y, vertices.at(1).x, imgSize);
	collection x12 = interpolate(vertices.at(1).y, vertices.at(1).x, vertices.at(2).y, vertices.at(2).x, imgSize);
	collection x02 = interpolate(vertices.at(0).y, vertices.at(0).x, vertices.at(2).y, vertices.at(2).x, imgSize);

	//x01 and x12 have common x coordinate
	//x01.pop_back();
	x01.insert(x01.end(), x12.begin(), x12.end()); //x012 

	//At this point we have left or right set of x in xo1 and in x02 and have to determine which one is
	if (!(x01.size() == 0 && x02.size() == 0))
	{
		collection xLeft, xRight;

		//Here we choose horizontal line and compare values of x in that line, the greater value is the right
		int m = x01.size() / 2;
		if (x02.at(m) < x01.at(m)) {
			xLeft = x02;
			xRight = x01;
		}
		else {
			xLeft = x01;
			xRight = x02;
		}

		int y0 = vertices.at(0).y;
		int y2 = vertices.at(2).y;

		for (int y = y0; y < y2; ++y) {
			for (int x = xLeft.at(y - y0); x < xRight.at(y - y0); ++x) {
				if (y >= 0 && y < imgSize.y && zBuffer.at(y * imgSize.x + x) > z)
				{
					zBuffer.at(y * imgSize.x + x) = z;
					image.setPixel(x, y, color);
				}
			}
		}
	}
}