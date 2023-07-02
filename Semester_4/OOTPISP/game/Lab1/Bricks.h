#pragma once
#include "Brick.h"
#include <SFML\Graphics.hpp>
#include <vector>

class Bricks
{
private:
	std::vector<Brick> m_bricks;
public:
	Bricks(const Brick& brick);
	Bricks(const std::vector<Brick>& bricks);
	Bricks();
	void addBrick(const Brick& brick);
	void removeBrick(const int index);
	std::vector<Brick>& get_bricks();
	Brick& operator[](const int index);
	int size();
	std::vector<DisplaysObject*> getBricks();
	static void handleEventBallBlockIntersection();
};

