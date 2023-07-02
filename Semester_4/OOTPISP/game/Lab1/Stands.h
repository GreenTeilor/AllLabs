#pragma once
#include "Stand.h"

class Stands
{
private:
	std::vector<Stand> m_stands;
public:
	Stands(const Stand& stand);
	Stands(const std::vector<Stand>& stands);
	void addStand(const Stand& stand);
	void removeStand(const int index);
	std::vector<Stand>& get_stands();
	Stand& operator[](const int index);
	int size();
	std::vector<DisplaysObject*> getStands();
};

