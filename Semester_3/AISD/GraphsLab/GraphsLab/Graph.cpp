#include "Graph.h"

Paths Graph::findPathPrivate(const std::vector<std::vector<int>>& a, std::vector<bool>& visited, int n, int v, int x, int currentPathLength, Paths& paths, Paths::Path& currentPath)
{
	//static Paths paths;
	//static Paths::Path currentPath;
	if (v == x) {
		currentPath.m_length = currentPathLength;
		paths.addPath(currentPath);
		return paths;
	}

	visited[v] = true;
	for (int i = 0; i < n; ++i)
		if (/*a[v][i]*/ a[v][i] != INFINITY_GRAPH && !visited[i])
		{
			currentPath.m_points.push_back({i, a[v][i]});
			currentPathLength += a[v][i];
			findPathPrivate(a, visited, n, i, x, currentPathLength, paths, currentPath);
			currentPath.m_points.pop_back();
			currentPathLength -= a[v][i];
		}
	visited[v] = false;
	return paths;
}

int Graph::minDist(const std::vector<int>& dist, const std::vector<bool>& tSet)
{

	int min = INT_MAX, index{ 0 };

	for (int i = 0; i < m_adjacencyMatrix.size(); ++i)
	{
		if (tSet[i] == false && dist[i] <= min)
		{
			min = dist[i];
			index = i;
		}

	}

	return index;
}

void Graph::initGraph(std::vector<std::vector<int>>& adjacencyMatrix)
{
	for (int i = 0; i < adjacencyMatrix.size(); ++i)
	{
		std::fill(adjacencyMatrix[i].begin(), adjacencyMatrix[i].end(), INFINITY_GRAPH);
		adjacencyMatrix[i][i] = 0;
	}
}

Graph::Graph(const std::vector<std::vector<int>>& adjacencyMatrix)
{
	m_adjacencyMatrix = adjacencyMatrix;
}

Paths Graph::findAllPaths(const int startPoint, const int finishPoint)
{
	std::vector<bool> visited{};
	visited.resize(m_adjacencyMatrix.size());
	Paths paths;
	Paths::Path currentPath;
	paths = this->findPathPrivate(m_adjacencyMatrix, visited, visited.size(), startPoint, finishPoint, 0, paths, currentPath);
	for (int i = 0; i < paths.getLength(); ++i)
		paths.insertInFront(i, { startPoint, 0});
	paths.sort();
	return paths;
}

Paths::Path Graph::findShortestPath(const int startPoint, const int finishPoint)
{
	std::vector<int> dist; // integer array to calculate minimum distance for each node.  
	dist.resize(m_adjacencyMatrix.size());
	std::fill(dist.begin(), dist.end(), /*INT_MAX*/INFINITY_GRAPH);
	std::vector<bool> tSet;// boolean array to mark visted/unvisted for each node.
	tSet.resize(m_adjacencyMatrix.size());
	std::fill(tSet.begin(), tSet.end(), false);

	dist[startPoint] = 0;

	for (int i = 0; i < dist.size(); ++i)
	{
		int m = minDist(dist, tSet); // vertex not yet included.
		tSet[m] = true;// m with minimum distance included in Tset.
		for (int i = 0; i < dist.size(); ++i)
		{
			// Updating the minimum distance for the particular node.
			if (!tSet[i] && /*m_adjacencyMatrix[m][i]*/ m_adjacencyMatrix[m][i] != INFINITY_GRAPH && dist[m] != /*INT_MAX*/INFINITY_GRAPH && dist[m] + m_adjacencyMatrix[m][i] < dist[i])
				dist[i] = dist[m] + m_adjacencyMatrix[m][i];
		}
	}

	Paths::Path path;
	if (dist[finishPoint] != /*INT_MAX*/INFINITY_GRAPH)
	{
		int current{ finishPoint };
		while (current != startPoint)
			for (int i = 0; i < m_adjacencyMatrix.size(); ++i)
				if (dist[current] - m_adjacencyMatrix[i][current] == dist[i] && m_adjacencyMatrix[i][current] != 0)
				{
					path.m_points.push_back({ current, m_adjacencyMatrix[i][current] });
					current = i;
					break;
				}
		path.m_points.push_back({ startPoint, 0 });
		path.m_length = dist[finishPoint];
		reverse(path.m_points.begin(), path.m_points.end());
	}
	return path;
}

Paths::Path Graph::findLongestPath(const int startPoint, const int finishPoint)
{
	Paths paths = findAllPaths(startPoint, finishPoint);
	if (paths.getLength())
		return paths[paths.getLength() - 1];
	return Paths::Path();
}

int Graph::findCenter()
{
	std::vector<std::vector<int>> m_adjacencyMatrixCopy{ m_adjacencyMatrix };
	//Floyd algorithm
	for (int k = 0; k < m_adjacencyMatrixCopy.size(); ++k)
		for (int i = 0; i < m_adjacencyMatrixCopy.size(); ++i)
			for (int j = 0; j < m_adjacencyMatrixCopy.size(); ++j)
				if (m_adjacencyMatrixCopy[i][k] != INFINITY_GRAPH && m_adjacencyMatrixCopy[k][j] != INFINITY_GRAPH)
					m_adjacencyMatrixCopy[i][j] = std::min(m_adjacencyMatrixCopy[i][j], m_adjacencyMatrixCopy[i][k] + m_adjacencyMatrixCopy[k][j]);

	//Find eccentricitys
	std::vector<int> eccentricitys;
	for (int i = 0; i < m_adjacencyMatrixCopy.size(); ++i)
	{
		int max{ 0 };
		for (int j = 0; j < m_adjacencyMatrixCopy.size(); ++j)
			if (m_adjacencyMatrixCopy[j][i] > max)
				max = m_adjacencyMatrixCopy[j][i];
		eccentricitys.push_back(max);
	}

	//Return lowest eccentricity
	//return *std::min_element(eccentricitys.begin(), eccentricitys.end());
	int minIndex{ 0 };
	for (int i = 1; i < eccentricitys.size(); ++i)
		if (eccentricitys[i] < eccentricitys[minIndex])
			minIndex = i;
	return minIndex;
}

void Graph::print_adjacencyMatrix()
{
	for (int i = 0; i < m_adjacencyMatrix.size(); ++i)
	{
		for (int j = 0; j < m_adjacencyMatrix.size(); ++j)
		{
			if (m_adjacencyMatrix[i][j] == INFINITY_GRAPH)
				printf("%7s", " inf");
			else
				printf(" %5d ", m_adjacencyMatrix[i][j]);
		}
		printf("\n");
	}
}