#include "Face.h"

Face::Face(std::vector<Component> components) : m_components{ components }
{
	for (const auto& part : m_components)
	{
		m_vertices.push_back(part.find(Part::V)->second);
		m_nVertices.push_back(part.find(Part::VN)->second);
		m_tVertices.push_back(part.find(Part::VT)->second);
	}
}

std::vector<std::vector<float>>& Face::getV()
{
	return m_vertices;
}

std::vector<std::vector<float>>& Face::getVN()
{
	return m_nVertices;
}

std::vector<std::vector<float>>& Face::getVT()
{
	return m_tVertices;
}