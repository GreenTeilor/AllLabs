#include "Bonuses.h"
//#include <time.h>
#include <random>

Bonuses::Bonuses(const Bonus& bonus)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(1, 100);

	m_bonuses.push_back(bonus);
	int percent = dist(gen);
	if (percent <= 20)
	{
		std::uniform_int_distribution<> dist2(1, 5);
		int bonusType = dist2(gen);
		switch (bonusType)
		{
		case 1: {
			m_bonuses[0].setType(Bonus::SPEEDSLOW);
			break;
		}
		case 2: {
			m_bonuses[0].setType(Bonus::SPEEDUP);
			break;
		}
		case 3: {
			m_bonuses[0].setType(Bonus::OFFCOLLISIONS);
			break;
		}
		case 4: {
			m_bonuses[0].setType(Bonus::DOWNBORDER);
			break;
		}
		case 5: {
			m_bonuses[0].setType(Bonus::POINTS);
			break;
		}
		default:
			break;
		}
	}
}

Bonuses::Bonuses()
{

}

Bonuses::Bonuses(const std::vector<Bonus>& bonuses)
{
	m_bonuses = bonuses;
}

void Bonuses::addBonus(Bonus bonus)
{
	if (bonus.canCast)
		m_bonuses.push_back(bonus);
}

void Bonuses::removeBonus(const int index)
{
	m_bonuses.erase(m_bonuses.begin() + index);
}

Bonus& Bonuses::operator[](const int index)
{
	return m_bonuses[index];
}

int Bonuses::size()
{
	return m_bonuses.size();
}

const Bonus& Bonuses::getBonus(int index) const
{
	return m_bonuses.at(0);
}

std::vector<Bonus>& Bonuses::get_bonuses()
{
	return m_bonuses;
}

std::vector<DisplaysObject*> Bonuses::getBonuses()
{
	std::vector<DisplaysObject*> shapes;
	for (int i = 0; i < m_bonuses.size(); ++i)
		shapes.push_back(&m_bonuses[i]);
	return shapes;
}