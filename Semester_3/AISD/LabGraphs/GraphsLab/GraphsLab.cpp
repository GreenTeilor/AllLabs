#include <iostream>
#include "Graph.h"
#include "Paths.h"

void createGraph1(std::vector<std::vector<int>>& mtrx1)
{
    const int verticesNum{ 5 };
    mtrx1.resize(verticesNum);
    for (int i = 0; i < verticesNum; ++i)
        mtrx1[i].resize(verticesNum);
    Graph::initGraph(mtrx1);
    mtrx1[0][1] = 10;
    mtrx1[0][3] = 30;
    mtrx1[0][4] = 100;
    mtrx1[1][2] = 50;
    mtrx1[2][4] = 10;
    mtrx1[3][2] = 20;
    mtrx1[3][4] = 60;
}

void createGraph2(std::vector<std::vector<int>>& mtrx2)
{
    const int verticesNum{ 7 };
    mtrx2.resize(verticesNum);
    for (int i = 0; i < verticesNum; ++i)
        mtrx2[i].resize(verticesNum);
    Graph::initGraph(mtrx2);
    
    
    mtrx2[0][1] = 10;
    mtrx2[1][2] = 1;
    mtrx2[1][4] = 10;
    mtrx2[2][5] = 2;
    mtrx2[3][0] = 10;
    mtrx2[3][1] = 10;
    mtrx2[3][2] = 10;
    mtrx2[4][6] = 4;
    mtrx2[5][4] = 3;
    mtrx2[5][3] = 10;
    mtrx2[6][5] = 10;
}

void createGraph3(std::vector<std::vector<int>>& mtrx3)
{
    const int verticesNum{ 5 };
    mtrx3.resize(verticesNum);
    for (int i = 0; i < verticesNum; ++i)
        mtrx3[i].resize(verticesNum);
    Graph::initGraph(mtrx3);


    mtrx3[0][1] = 1;
    mtrx3[1][2] = 2;
    mtrx3[3][1] = 1;
    mtrx3[3][2] = 3;
    mtrx3[4][3] = 5;
    mtrx3[2][4] = 4;
    mtrx3[2][3] = 2;
}

int main()
{
    std::vector<std::vector<int>> mtrx;
    //createGraph1(mtrx);
    createGraph3(mtrx);
    Graph graph{ mtrx };

    Paths paths;

    paths = graph.findAllPaths(0, 4);
    printf("All paths from 1 to 5 in ascending order:\n");
    paths.printPaths();



    printf("\n");
    Paths::Path path;

    printf("Shortest path: ");
    path = graph.findShortestPath(0, 4);
    Paths::printPath(path);

    printf("\n");
    printf("Longest path: ");
    path = graph.findLongestPath(0, 4);
    Paths::printPath(path);

    printf("\n");
    printf("Graph center: %d\n",graph.findCenter());
}
