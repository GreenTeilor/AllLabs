#pragma once
#include <string>
#include <map>

class ObjType
{
public:
	enum TypeEnum
	{
		V,
		VT,
		VN,
		F,
		FILE_END,
		COUNT
	};
	static const std::map<std::string, TypeEnum> typeMap;

private:
	TypeEnum m_type;

public:
	ObjType(TypeEnum type);
	operator TypeEnum() const;
};

