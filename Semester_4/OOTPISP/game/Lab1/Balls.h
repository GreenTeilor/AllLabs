#pragma once
#include "Ball.h"
#include <vector>

class Balls
{
private:
	std::vector<Ball> m_balls;
public:
	Balls(const Ball& ball);
	Balls(const std::vector<Ball>& balls);
	void addBall(const Ball& ball);
	void removeBall(const int index);
	std::vector<Ball>& get_balls();
	Ball& operator[](const int index);
	int size();
	std::vector<DisplaysObject*> getBalls();
};

