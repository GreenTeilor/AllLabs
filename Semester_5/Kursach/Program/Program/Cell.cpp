#include "Cell.h"

Cell::Cell() : m_inner{ Type::Types::EMPTY }, m_cover{ Type::Types::CLOSED }, m_isOpened{ false }
{

}

Type Cell::getInner()
{
	return m_inner;
}

void Cell::setInner(Type inner)
{
	m_inner = inner;
}

Type Cell::getCover()
{
	return m_cover;
}

void Cell::setCover(Type cover)
{
	m_cover = cover;
}

bool Cell::isOpened()
{
	return m_isOpened;
}

Type Cell::getType()
{
	return m_isOpened ? m_inner : m_cover;
}

Type Cell::changeFlag()
{
	if (!m_isOpened)
	{
		if (m_cover == Type::Types::FLAG)
		{
			m_cover = Type::Types::CLOSED;
		}
		else
		{
			m_cover = Type::Types::FLAG;
		}
		return m_cover;
	}
	return m_inner;
}

bool Cell::open()
{
	if (m_cover != Type::Types::FLAG)
	{
		m_isOpened = true;
		return true;
	}
	return false;
}