#include "Stands.h"

Stands::Stands(const Stand& stand)
{
	m_stands.push_back(stand);
}

Stands::Stands(const std::vector<Stand>& stands)
{
	m_stands = stands;
}

void Stands::addStand(const Stand& stand)
{
	m_stands.push_back(stand);
}

void Stands::removeStand(const int index)
{
	m_stands.erase(m_stands.begin() + index);
}

std::vector<Stand>& Stands::get_stands()
{
	return m_stands;
}

Stand& Stands::operator[](const int index)
{
	return m_stands[index];
}

int Stands::size()
{
	return m_stands.size();
}

std::vector<DisplaysObject*> Stands::getStands()
{
	std::vector<DisplaysObject*> shapes;
	for (int i = 0; i < m_stands.size(); ++i)
		shapes.push_back(&m_stands[i]);
	return shapes;
}