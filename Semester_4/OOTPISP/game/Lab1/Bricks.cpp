#include "Bricks.h"
#include "EventIntersectionBallBlock.h"
#include "TellPoints.h"

Bricks::Bricks(const Brick& brick)
{
	m_bricks.push_back(brick);
}

Bricks::Bricks(const std::vector<Brick>& bricks)
{
	m_bricks = bricks;
}

Bricks::Bricks()
{

}

void Bricks::addBrick(const Brick& brick)
{
	m_bricks.push_back(brick);
}

void Bricks::removeBrick(const int index)
{
	m_bricks.erase(m_bricks.begin() + index);
}

std::vector<Brick>& Bricks::get_bricks()
{
	return m_bricks;
}

Brick& Bricks::operator[](const int index)
{
	return m_bricks[index];
}

int Bricks::size()
{
	return m_bricks.size();
}

std::vector<DisplaysObject*> Bricks::getBricks()
{
	std::vector<DisplaysObject*> shapes;
	for (int i = 0; i < m_bricks.size(); ++i)
		shapes.push_back(&m_bricks[i]);
	return shapes;
}

void Bricks::handleEventBallBlockIntersection()
{
	if (EventIntersectionBallBlock::index != -1)
	{
		TellPoints::enable(1);
		EventIntersectionBallBlock::bricksPtr->removeBrick(EventIntersectionBallBlock::index);
		EventIntersectionBallBlock::happened = false;
		EventIntersectionBallBlock::index = -1;
	}
}