#pragma once
#include "Type.h"

class Cell
{
private:
	Type m_inner;
	Type m_cover;
	bool m_isOpened;

public:
	Cell();
	Type getInner();
	void setInner(Type inner);
	Type getCover();
	void setCover(Type cover);
	bool isOpened();
	Type getType();
	Type changeFlag();
	bool open();
};

