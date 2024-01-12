#include "Sprite.h"

Sprite::Sprite(HWND hwnd, RECT workSpace)
{
	m_device = GetDC(hwnd);
	m_bufferDevice = CreateCompatibleDC(m_device);
	this->m_workSpace = workSpace;

	m_hScreen = CreateCompatibleBitmap(m_device, workSpace.right, workSpace.bottom);
	m_oldBmp = (HBITMAP)SelectObject(m_bufferDevice, m_hScreen);

	m_image = (HBITMAP)LoadImage(0, L"images/snail.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(m_image, sizeof(BITMAP), &m_bm);
	m_spriteDevice = CreateCompatibleDC(m_device);
	m_oldImage = (HBITMAP)SelectObject(m_spriteDevice, m_image);
}

void Sprite::draw(HWND hWnd, float X, float Y)
{
	BeginPaint(hWnd, &m_PStruct);

	//Redraw window background
	PatBlt(m_bufferDevice, 0, 0, m_workSpace.right, m_workSpace.bottom, WHITENESS);

	//Move from context m_spriteDevice to context m_bufferDevice
	BitBlt(m_bufferDevice, (int)X, (int)Y, m_bm.bmWidth, m_bm.bmHeight, m_spriteDevice, 0, 0, SRCCOPY);

	//Move from context m_bufferDevice to context m_device
	BitBlt(m_device, 0, 0, m_workSpace.right, m_workSpace.bottom, m_bufferDevice, 0, 0, SRCCOPY);

	EndPaint(hWnd, &m_PStruct);
}

CenterPoints* Sprite::center(float width, float height)
{
	m_points.x = -width / 2;
	m_points.y = -height / 2;
	return &m_points;
}

Sprite::~Sprite() 
{
	//For screen
	SelectObject(m_bufferDevice, m_oldBmp);
	DeleteObject(m_hScreen);
	DeleteDC(m_bufferDevice);

	//For image
	SelectObject(m_spriteDevice, m_oldImage);
	DeleteObject(m_image);
	DeleteDC(m_spriteDevice);
}