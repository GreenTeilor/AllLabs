#pragma once
#include <vector>
#include <algorithm>
#include "Paths.h"
#define INFINITY_GRAPH INT_MAX

class Graph
{
private:
	std::vector<std::vector<int>> m_adjacencyMatrix;

	//Recursive function which returns all paths from point v to point x
	Paths findPathPrivate(const std::vector<std::vector<int>>& a, std::vector<bool>& visited, int n, int v, int x, int currentPathLength, Paths& paths, Paths::Path& currentPath);

	//Returns minimum distance from all unvisited vertices to current
	int minDist(const std::vector<int>& dist, const std::vector<bool>& tSet);

public:
	//Initialize adjacency matrix from parameter with 0(MACHINE INFINITY)
	static void initGraph(std::vector<std::vector<int>>& adjacencyMatrix);

	//Constructor copy adjacency matrix from parameter to class field
	Graph(const std::vector<std::vector<int>>& adjacencyMatrix);

	//This function calls recursive function findPathPrivate, but prepare all parameters to simplify usage for developer
	Paths findAllPaths(const int startPoint, const int finishPoint);

	//Function finds shortest path between two points
	Paths::Path findShortestPath(const int startPoint, const int finishPoint);

	//Function finds longest path between two points
	Paths::Path findLongestPath(const int startPoint, const int finishPoint);

	//Finds graph center
	int findCenter();
};

