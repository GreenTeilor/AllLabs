#include "Face.h"

Face::Face(std::vector<Component> components) : m_components{ components }
{
	for (const auto& part : m_components)
	{
		m_vertices.push_back(part.find(Part::V)->second);
	}
}

std::vector<std::vector<float>>& Face::getV()
{
	return m_vertices;
}