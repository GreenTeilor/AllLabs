#include "Players.h"

Players::Players(const Player& player)
{
	m_players.push_back(player);
}

void Players::addPlayer(const Player& player)
{
	m_players.push_back(player);
}

void Players::removePlayer(const int index)
{
	m_players.erase(m_players.begin() + index);
}

Player& Players::operator[](const int index)
{
	return m_players[index];
}