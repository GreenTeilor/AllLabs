#pragma once
#include "Termin.h"

class ObjectPointer
{
	Termin termin;
	Termin* next;

public:
	ObjectPointer();
	bool addTermin(const std::string& name, int pagesNum);
};