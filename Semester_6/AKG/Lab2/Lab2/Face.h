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
public:
	Face(std::vector<Component>);
	std::vector<std::vector<float>>& getV();
};

