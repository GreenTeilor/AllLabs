#include "Paths.h"

void Paths::printPath(const Path& path)
{
	if (path.m_points.size())
	{
		printf("<%d>", path.m_points[0].m_point + 1);
		for (int j = 1; j < path.m_points.size(); ++j)
			printf("  (%d)->  <%d>", path.m_points[j].m_distancePrev, path.m_points[j].m_point + 1);
		printf("  Количество точек: %d, Длина: %d", (int)path.m_points.size(), path.m_length);
		printf("\n");
	}
}

Paths::Paths(const Paths& paths)
{
	this->m_paths = paths.m_paths;
}

Paths::Paths()
{
	m_paths.resize(0);
}

const Paths& Paths::operator=(const Paths& paths)
{
	this->m_paths = paths.m_paths;
	return *this;
}

Paths::Path& Paths::operator[](const int index)
{
	return m_paths[index];
}

void Paths::addPath(const Path& path)
{
	m_paths.push_back(path);
}

void Paths::clear()
{
	m_paths.resize(0);
}

int Paths::getLength()
{
	return m_paths.size();
}

void Paths::insertInFront(const int pathIndex, const DistancePoint& distancePoint)
{
	m_paths[pathIndex].m_points.insert(m_paths[pathIndex].m_points.begin(), distancePoint);
}

void Paths::sort()
{
	for (int i = 1; i < m_paths.size(); ++i)
		for (int j = 0; j < m_paths.size() - i; ++j)
			if (m_paths[j].m_length > m_paths[j + 1].m_length)
			{
				Path temp = m_paths[j];
				m_paths[j] = m_paths[j + 1];
				m_paths[j + 1] = temp;
			}
}

void Paths::printPaths()
{
	int i{ 1 };
	for (const Path& path : m_paths)
	{
		printf("Path #%d: ", i);
		this->printPath(path);
		++i;
	}
}