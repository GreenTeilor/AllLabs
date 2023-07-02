#pragma once
#include "Bonus.h"
#include "Balls.h"
#include <map>
#include <cassert>

class ActiveBonuses
{
public:
	struct State
	{
		double m_activeTime;
		bool isActive;
	};

private:
	sf::Clock timer;
	std::map<Bonus::Type, State> m_activeBonuses;
	double speedControl;

	void disactivate(Bonus::Type type, Balls& balls);
	std::string typeToString(Bonus::Type type) const;

public:
	ActiveBonuses();
	void setActive(Bonus::Type type, Balls& balls);
	void tick(Balls& balls);
	void resetTimer();
	const std::map<Bonus::Type, State>& get_activeBonuses() const;
	std::map<std::string, State> get_bonuses() const;
	void from_json(const std::map<std::string, State>& map);
	void draw(sf::RenderWindow& window);
};

