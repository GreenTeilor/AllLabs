#include "Balls.h"

Balls::Balls(const Ball& ball)
{
	m_balls.push_back(ball);
}

Balls::Balls(const std::vector<Ball>& balls)
{
	m_balls = balls;
}

void Balls::addBall(const Ball& ball)
{
	m_balls.push_back(ball);
}

void Balls::removeBall(const int index)
{
	m_balls.erase(m_balls.begin() + index);
}

std::vector<Ball>& Balls::get_balls()
{
	return m_balls;
}

Ball& Balls::operator[](const int index)
{
	return m_balls[index];
}

int Balls::size()
{
	return m_balls.size();
}

std::vector<DisplaysObject*> Balls::getBalls()
{
	std::vector<DisplaysObject*> shapes;
	for (int i = 0; i < m_balls.size(); ++i)
		shapes.push_back(&m_balls[i]);
	return shapes;
}

