#include "ObjType.h"

const std::map<std::string, ObjType::TypeEnum> ObjType::typeMap =
{
	{"v", V},
	{"vt", VT},
	{"vn", VN},
	{"f", F}
};

ObjType::ObjType(TypeEnum type) : m_type{ type }
{

}

ObjType::operator TypeEnum() const
{
	return m_type;
}