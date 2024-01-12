#include "Type.h"

Type::Type(Types type) : m_type{ type }, m_imagePath{ typeImagePath.at(type) }
{

}

Type::operator std::string() const 
{
	return m_imagePath;
}

Type::operator Types() const
{
	return m_type;
}

bool Type::operator == (const Type& type)
{
	return m_type == type.m_type;
}

bool Type::operator == (const Types& type)
{
	return m_type == type;
}

bool Type::operator != (const Type& type)
{
	return m_type != type.m_type;
}

bool Type::operator != (const Types& type)
{
	return m_type != type;
}

Type& Type::operator = (const Types& type)
{
	m_type = type;
	m_imagePath = typeImagePath.at(type);
	return *this;
}

std::map<Type::Types, std::string> Type::getTypesAndPaths()
{
	return typeImagePath;
}