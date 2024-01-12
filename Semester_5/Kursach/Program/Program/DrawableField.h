#pragma once
#include "Field.h"
#include "framework.h"
#include "Const.h"

class DrawableField
{
private:
	HWND& m_hWnd;
	HINSTANCE& m_hInst;
	Field& m_field;
	std::vector<HWND> m_buttons;
	std::vector<HBITMAP> m_images;
public:
	DrawableField(Field& field, HWND& hWnd, HINSTANCE& hInst);
	void update(bool isRecreateButtons, SUBCLASSPROC fieldActions);
};

