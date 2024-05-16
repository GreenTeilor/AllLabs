#pragma once
#include <vector>
#include <map>


class Face
{

public:
	enum class Part
	{
		V,
		VT,
		VN
	};
	using Component = std::map<Part, std::vector<float>&>;

private:
	std::vector<Component> m_components;
	std::vector<std::vector<float>> m_vertices;
	std::vector<std::vector<float>> m_nVertices;
	std::vector<std::vector<float>> m_tVertices;
public:
	Face(std::vector<Component>);
	std::vector<std::vector<float>>& getV();
	std::vector<std::vector<float>>& getVN();
	std::vector<std::vector<float>>& getVT();
};

