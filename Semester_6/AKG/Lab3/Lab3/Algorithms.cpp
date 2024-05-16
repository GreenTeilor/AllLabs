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

Algorithms::collection Algorithms::interpolate(float i0, float d0, float i1, float d1, const sf::Vector2u& imgSize) {
	collection values{};
	values.reserve(100);
	float a = (float)(d1 - d0) / (i1 - i0);
	float d = d0;
	float i = i0;
	while (i < i1) {
		values.push_back(d);
		d += a;
		i += 0.1f;
	}
	return values;
}

glm::vec3 Algorithms::interpolateVectors(const glm::vec3& vec1, const glm::vec3& vec2, const glm::vec3& vec3, const float w1, const float w2, const float w3)
{
	return w1 * vec1 + w2 * vec2 + w3 * vec3;
}

void Algorithms::rasterTriangle(std::vector<glm::vec4>& vertices, std::vector<glm::vec3>& worldVertices, std::vector<glm::vec3>& normals, const glm::vec3& cameraPos,
	sf::Image& image, const glm::vec3& ambientLight, std::vector<float>& zBuffer, const float z,
	const float diffuseLightStrength, const glm::vec3& diffuseLightColor, const glm::vec3& objectColor, const float specularStrength, const glm::mat4& mvp)
{
	auto imgSize = image.getSize();
	const glm::vec3& lightPos{ cameraPos };

	if ((vertices.at(0).x < 0 || vertices.at(0).x >= imgSize.x || vertices.at(0).y < 0 || vertices.at(0).y >= imgSize.y)
		&& (vertices.at(1).x < 0 || vertices.at(1).x >= imgSize.x || vertices.at(1).y < 0 || vertices.at(1).y >= imgSize.y)
		&& (vertices.at(2).x < 0 || vertices.at(2).x >= imgSize.x || vertices.at(2).y < 0 || vertices.at(2).y >= imgSize.y))
		return;

	if (vertices.at(1).y < vertices.at(0).y) { std::swap(vertices.at(0), vertices.at(1)); std::swap(worldVertices.at(0), worldVertices.at(1)); std::swap(normals.at(0), normals.at(1)); }
	if (vertices.at(2).y < vertices.at(0).y) { std::swap(vertices.at(2), vertices.at(0)); std::swap(worldVertices.at(2), worldVertices.at(0)); std::swap(normals.at(2), normals.at(0)); }
	if (vertices.at(2).y < vertices.at(1).y) { std::swap(vertices.at(2), vertices.at(1)); std::swap(worldVertices.at(2), worldVertices.at(1)); std::swap(normals.at(2), normals.at(1)); }

	const glm::vec4& v1 = vertices.at(0);
	const glm::vec4& v2 = vertices.at(1);
	const glm::vec4& v3 = vertices.at(2);

	glm::vec3 d1{ v2 - v1 };
	glm::vec3 d2{ v3 - v1 };
	glm::vec3 d3{ v3 - v2 };

	float kx1 = d1.x / d1.y;
	float kx2 = d2.x / d2.y;
	float kx3 = d3.x / d3.y;
	float kz1 = d1.z / d1.y;
	float kz2 = d2.z / d2.y;
	float kz3 = d3.z / d3.y;

	const glm::vec3& vn1 = normals.at(0);
	const glm::vec3& vn2 = normals.at(1);
	const glm::vec3& vn3 = normals.at(2);

	//in world coordinates
	glm::vec3 dn1 = vn2 - vn1;
	glm::vec3 dn2 = vn3 - vn1;
	glm::vec3 dn3 = vn3 - vn2;
	glm::vec3 kn1 = dn1 / d1.y;
	glm::vec3 kn2 = dn2 / d2.y;
	glm::vec3 kn3 = dn3 / d3.y;

	const glm::vec3& wv1 = worldVertices.at(0);
	const glm::vec3& wv2 = worldVertices.at(1);
	const glm::vec3& wv3 = worldVertices.at(2);

	glm::vec3 d1W{ wv2 - wv1 };
	glm::vec3 d2W{ wv3 - wv1 };
	glm::vec3 d3W{ wv3 - wv2 };

	glm::vec3 k1W{ d1W / d1.y };
	glm::vec3 k2W{ d2W / d2.y };
	glm::vec3 k3W{ d3W / d3.y };


	int topY = (int)std::max(std::ceil(v1.y), 0.0f);
	int bottomY = (int)std::min(std::ceil(v3.y), (float)(imgSize.y - 1));

	for (int y = topY; y < bottomY; y++) {
		float crossX1 = y < v2.y ? v1.x + kx1 * (y - v1.y) : v2.x + kx3 * (y - v2.y);
		float crossX2 = v1.x + kx2 * (y - v1.y);
		float crossZ1 = y < v2.y ? v1.z + kz1 * (y - v1.y) : v2.z + kz3 * (y - v2.y);
		float crossZ2 = v1.z + kz2 * (y - v1.y);

		float crossX1W = y < v2.y ? wv1.x + k1W.x * (y - v1.y) : wv2.x + k3W.x * (y - v2.y);
		float crossX2W = wv1.x + k2W.x * (y - v1.y);

		float crossY1W = y < v2.y ? wv1.y + k1W.y * (y - v1.y) : wv2.y + k3W.y * (y - v2.y);
		float crossY2W = wv1.y + k2W.y * (y - v1.y);
		float crossZ1W = y < v2.y ? wv1.z + k1W.z * (y - v1.y) : wv2.z + k3W.z * (y - v2.y);
		float crossZ2W = wv1.z + k2W.z * (y - v1.y);

		glm::vec3 crossN1 = (y < v2.y) ? (vn1 + kn1 * (y - v1.y)) : (vn2 + kn3 * (y - v2.y));
		glm::vec3 crossN2 = vn1 + kn2 * (y - v1.y);

		if (crossX1 > crossX2) {
			float temp = crossX1;
			crossX1 = crossX2;
			crossX2 = temp;
			temp = crossZ1;
			crossZ1 = crossZ2;
			crossZ2 = temp;
			temp = crossX1W;
			glm::vec3 temp2 = crossN1;
			crossX1W = crossX2W;
			crossX2W = temp;
			temp = crossY2W;
			crossY2W = crossY1W;
			crossY1W = temp;
			temp = crossZ1W;
			crossZ1W = crossZ2W;
			crossZ2W = temp;
			crossN1 = crossN2;
			crossN2 = temp2;
		}
		float kz = (crossZ2 - crossZ1) / (crossX2 - crossX1);
		
		int leftX = (int)std::max(std::ceil(crossX1), 0.0f);
		int rightX = (int)std::min(std::ceil(crossX2), (float)(imgSize.x - 1));

		float kxW = (crossX2W - crossX1W) / (crossX2 - crossX1);
		float kyW = (crossY2W - crossY1W) / (crossX2 - crossX1);
		float kzW = (crossZ2W - crossZ1W) / (crossX2 - crossX1);

		glm::vec3 kn = (crossN2 - crossN1) / (crossX2 - crossX1);

		for (int x = leftX; x < rightX; x++) {
			float z = crossZ1 + kz * (x - crossX1);
			float xW = crossX1W + kxW * (x - crossX1);
			float yW = crossY1W + kyW * (x - crossX1);
			float zW = crossZ1W + kzW * (x - crossX1);

			glm::vec3 d = kn * ((float)x - crossX1);
			glm::vec3 b = crossN1 + d;
			const glm::vec3& curN = glm::normalize(b);

			if ((zBuffer.at(y * imgSize.x + x) > z)) {
				zBuffer.at(y * imgSize.x + x) = z;

				glm::vec3 pointWorld{ xW, yW, zW };
				
				const glm::vec3& pointNormal = curN;

				//Diffuse light
				glm::vec3 reversLightVector{ lightPos - pointWorld };
				float lightIntensity = glm::dot(pointNormal, glm::normalize(reversLightVector));
				if (lightIntensity < 0)
				{
					lightIntensity = 0.0f;
				}
				glm::vec3 diffuseLight{ lightIntensity * diffuseLightStrength * diffuseLightColor };

				//Specular light
				glm::vec3 viewDir = glm::normalize(cameraPos - pointWorld);
				glm::vec3 reflectDir = glm::reflect(glm::normalize(-reversLightVector), pointNormal);
				float spec = pow(std::max(dot(viewDir, reflectDir), 0.0f), 4);
				glm::vec3 specularLight{ specularStrength * 0.002f * spec * diffuseLightColor };

				glm::vec3 fongLight = (diffuseLight + ambientLight + specularLight) * objectColor;
				glm::ivec3 colorComponents{ std::min(255.0f, fongLight.x), std::min(255.0f, fongLight.y), std::min(255.0f, fongLight.z) };

				image.setPixel(x, y, sf::Color{ (sf::Uint8)colorComponents.x, (sf::Uint8)colorComponents.y, (sf::Uint8)colorComponents.z });
			}
		}
	}
}