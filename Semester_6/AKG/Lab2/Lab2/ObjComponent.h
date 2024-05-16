#pragma once
#include "ObjType.h"
#include "vector"

class ObjComponent
{
private:
	ObjType m_type;
	std::vector<std::string> m_values;

public:
	ObjComponent(ObjType type, std::vector<std::string> values);
	ObjComponent();
	ObjType getType();
	std::vector<std::string> getValues();
};

