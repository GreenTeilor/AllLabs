#pragma once
#include "DisplaysObject.h"

class Bonus : public DisplaysObject
{
public:
	enum Type
	{
		NONE,
		SPEEDSLOW,
		SPEEDUP,
		OFFCOLLISIONS,
		DOWNBORDER,
		POINTS
	};
	bool canCast = false;

private:
	Type m_type;

public:
	Bonus(const sf::Sprite& bobusImage, int bonusHeight,
		int bonusWidth, int bonuscoordinateX, int bonuscoordinateY, const Type& type = NONE);
	Bonus();
	void cast();
	void draw(sf::RenderWindow& window);
	void changeCast();
	void setType(Type type);
	Type getType() const;
	virtual void move() override;
	bool operator==(const Bonus& bonus);
};

