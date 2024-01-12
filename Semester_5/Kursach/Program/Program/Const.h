#pragma once
#include <map>
#include <string>
#include "framework.h"
#include "Type.h"

class Const
{
public:
	static inline int imgWidth = 20;
	static inline int imgHeight = 20;
	static inline int smileWidth = 26;
	static inline int smileHeight = 26;
	static inline int digitsWidth = 187;
	static inline int digitsHeight = 23;
	static inline int interfaceElementsTopGap = 5;
	static inline std::map<Type::Types, HBITMAP> images{};
	static void loadImages();
};

