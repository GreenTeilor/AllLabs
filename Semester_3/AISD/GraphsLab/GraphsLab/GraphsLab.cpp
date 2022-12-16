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
    setlocale(LC_ALL, "Russian");
    int mtrxNum{ 0 };
    std::cout << "Введите номер графа для загрузки(доступно 3): ";
    std::cin >> mtrxNum;
    std::vector<std::vector<int>> mtrx;
    switch (mtrxNum)
    {
    case 1:
        createGraph1(mtrx);
        break;
    case 2:
        createGraph2(mtrx);
        break;
    case 3:
        createGraph3(mtrx);
        break;
    default:
        exit(0);
    }
    
    Graph graph{ mtrx };

    int start{ 0 };
    int finish{ 0 };
    std::cout << "Введите начальную точку: ";
    std::cin >> start;
    std::cout << "Введите конечную точку: ";
    std::cin >> finish;
    --start;
    --finish;

    printf("Матрица смежности графа:\n");
    graph.print_adjacencyMatrix();

    Paths paths;

    paths = graph.findAllPaths(start, finish);
    if (paths.getLength())
    {
        printf("\n\n\n");
        printf("Все пути в графе от точки %d до точки %d по возрастанию длины:\n", start + 1, finish + 1);
        paths.printPaths();
        printf("\n\n");


        printf("\n");
        Paths::Path path;

        printf("Кратчайший путь: ");
        path = graph.findShortestPath(start, finish);
        Paths::printPath(path);

        printf("\n");
        printf("Длиннейший путь: ");
        path = graph.findLongestPath(start, finish);
        Paths::printPath(path);
    }
    else
        printf("\nВершина %d недостижима из вершины %d", finish + 1, start + 1);

    printf("\n");
    printf("\nЦентр графа: %d\n",graph.findCenter() + 1);
}
