#pragma once
#include <map>
#include <string>
#include <vector>

class Type
{
public:
	enum class Types
	{
		BOMB = -5, BOMB_BOOM, EMPTY, CLOSED, FLAG, WRONG_FLAG,
		NUMBER_1, NUMBER_2, NUMBER_3, NUMBER_4,
		NUMBER_5, NUMBER_6, NUMBER_7, NUMBER_8,
		SMILE_HAPPY, SMILE_SHOCKED, SMILE_DEAD, SMILE_COOL, DIGITS
	};

private:
	static inline std::map<Types, std::string> typeImagePath =
	{
		{Types::BOMB, "bomb"},
		{Types::BOMB_BOOM, "bomb_boom"},
		{Types::EMPTY, "empty"},
		{Types::CLOSED, "closed"},
		{Types::FLAG, "flag"},
		{Types::WRONG_FLAG, "wrongFlag"},
		{Types::NUMBER_1, "1"},
		{Types::NUMBER_2, "2"},
		{Types::NUMBER_3, "3"},
		{Types::NUMBER_4, "4"},
		{Types::NUMBER_5, "5"},
		{Types::NUMBER_6, "6"},
		{Types::NUMBER_7, "7"},
		{Types::NUMBER_8, "8"},
		{Types::SMILE_HAPPY, "smile_happy"},
		{Types::SMILE_SHOCKED, "smile_shocked"},
		{Types::SMILE_DEAD, "smile_dead"},
		{Types::SMILE_COOL, "smile_cool"},
		{Types::DIGITS, "digits"}
	};
	Types m_type;
	std::string m_imagePath;

public:
	Type(Types type);
	operator std::string() const;
	operator Types() const;
	bool operator == (const Type& type);
	bool operator == (const Types& type);
	bool operator != (const Type& type);
	bool operator != (const Types& type);
	Type& operator = (const Types& type);
	static std::map<Types, std::string> getTypesAndPaths();
};

