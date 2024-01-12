#pragma once
#include <Windows.h>

struct CenterPoints
{
	float x, y;
};

class Sprite
{
	HDC m_device;
	HDC m_bufferDevice;
	HBITMAP m_hScreen;
	HBITMAP m_oldBmp;
	RECT m_workSpace;
	PAINTSTRUCT m_PStruct;
	CenterPoints m_points;

	BITMAP m_bm;
	HDC m_spriteDevice;
	HBITMAP m_image;
	HBITMAP m_oldImage;

public:
	Sprite(HWND hwnd, RECT workSpace);

	void draw(HWND hWnd, float X, float Y);
	CenterPoints* center(float width, float height);
	~Sprite();
};

