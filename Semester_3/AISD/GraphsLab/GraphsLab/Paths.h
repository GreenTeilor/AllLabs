#pragma once
#include <vector>

class Paths
{
public:
	struct DistancePoint
	{
		int m_point;
		int m_distancePrev;
	};

	struct Path
	{
		std::vector<DistancePoint> m_points;
		int m_length;
	};

private:
	std::vector<Path> m_paths;

public:
	static void printPath(const Path& path);

	Paths(const Paths& paths);

	Paths();

	const Paths& operator=(const Paths& paths);

	Path& operator[](const int index);

	void addPath(const Path& path);

	void clear();

	int getLength();

	void insertInFront(const int pathIndex, const DistancePoint& distancePoint);

	void sort();

	void printPaths();

};