#include "ObjComponent.h"

ObjComponent::ObjComponent(ObjType type, std::vector<std::string> values) : m_type{ type }, m_values{ values }
{
	
}

ObjComponent::ObjComponent() : m_type{ObjType::COUNT}, m_values{}
{

}

ObjType ObjComponent::getType()
{
	return m_type;
}

std::vector<std::string> ObjComponent::getValues()
{
	return m_values;
}