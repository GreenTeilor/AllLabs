#pragma once
#include "Player.h"
#include <vector>

class Players
{
private:
	std::vector<Player> m_players;
public:
	Players(const Player& player);
	void addPlayer(const Player& player);
	void removePlayer(const int index);
	Player& operator[](const int index);
};

