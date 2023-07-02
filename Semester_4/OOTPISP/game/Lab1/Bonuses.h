#pragma once
#include "Bonus.h"
#include <vector>

class Bonuses
{
private:
	std::vector<Bonus> m_bonuses;
public:
	Bonuses(const Bonus& bonus);
	Bonuses();
	Bonuses(const std::vector<Bonus>& bonuses);
	void addBonus(Bonus bonus);
	void removeBonus(const int bonus);
	const Bonus& getBonus(const int index) const;
	std::vector<Bonus>& get_bonuses();
	std::vector<DisplaysObject*> getBonuses();
	Bonus& operator[](const int index);
	int size();
};
