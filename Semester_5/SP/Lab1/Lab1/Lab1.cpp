#include "Sprite.h"
#include <Windows.h>
#include <cmath>
#include <chrono>
#include <thread>

Sprite* sprite;
CenterPoints* centerPoints;
RECT dimension = { 0, 0, 1800, 900 };
float X = 0.0f;
float Y = 0.0f;
float pictureWidth = 100.0f;
float pictureHeight = 61.0f;
const float SPEED = 1.f;
const float WHEELSPEED = 15.f;

//To make smooth bouncing
const int SLEEP_TIME = 100;

const int BOUNCE_DISTANCE = 50;
const float BOUNCE_MOVEMENT_STEP = 0.5f;
bool yTop = false;
bool yBot = false;
bool xRight = false;
bool xLeft = false;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// Wheel spin
	if (uMsg == WM_MOUSEWHEEL && GET_KEYSTATE_WPARAM(wParam) == MK_SHIFT)
	{
		if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
			X += WHEELSPEED;
		else
			X -= WHEELSPEED;
	}
	else if (uMsg == WM_MOUSEWHEEL && GET_KEYSTATE_WPARAM(wParam) != MK_SHIFT)
	{
		if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
			Y += WHEELSPEED;
		else
			Y -= WHEELSPEED;
	}

	// Window destruction
	if (uMsg == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}

	if (uMsg == WM_PAINT)
	{
		sprite->draw(hwnd, X, Y);
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR cmdLine, int nCmdShow)
{
	WNDCLASSEX windowClass;
	MSG message;
	POINT mouseCoords;
	float distance = 0.0f;

	ZeroMemory(&windowClass, sizeof(WNDCLASSEX));
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowClass.hInstance = hInstance;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.lpszClassName = L"MainWindow";
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClassEx(&windowClass);

	AdjustWindowRectEx(&dimension, WS_OVERLAPPEDWINDOW, NULL, WS_EX_OVERLAPPEDWINDOW);

	HWND winHandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MainWindow", L"Moving Figure", WS_OVERLAPPEDWINDOW,
		100, 100, dimension.right - dimension.left, dimension.bottom - dimension.top, NULL, NULL, hInstance, 0);

	if (!winHandle) return -1;

	//Initial sprite position
	X = (dimension.right - dimension.left) / 2.f;
	Y = (dimension.bottom - dimension.top) / 2.f;

	message.message = WM_NULL;

	//Sprite creation
	sprite = new Sprite(winHandle, dimension);
	if (!sprite) return -1;
	centerPoints = sprite->center(pictureWidth, pictureHeight);

	ShowWindow(winHandle, nCmdShow);

	//App cycle
	while (message.message != WM_QUIT)
	{
		GetClientRect(winHandle, &dimension);

		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			DispatchMessage(&message);
		}

		//Check mouse button click
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			//Obtain cursor position
			GetCursorPos(&mouseCoords);

			//Screen coordinates to client coordinates
			ScreenToClient(winHandle, &mouseCoords);

			mouseCoords.x += centerPoints->x; mouseCoords.y += centerPoints->y;

			//Can be commented to instantly move sprite
			distance = sqrt((mouseCoords.x - X) * (mouseCoords.x - X) + (mouseCoords.y - Y) * (mouseCoords.y - Y));

			X += SPEED * (mouseCoords.x - X) / distance;
			Y += SPEED * (mouseCoords.y - Y) / distance;

			//To avoid shaking
			if (distance < 0.5f)
			{
				X = mouseCoords.x;
				Y = mouseCoords.y;
			}
		}

		//Move by arrows
		if (GetAsyncKeyState(VK_UP))
			Y -= SPEED;
		if (GetAsyncKeyState(VK_DOWN))
			Y += SPEED;
		if (GetAsyncKeyState(VK_LEFT))
			X -= SPEED;
		if (GetAsyncKeyState(VK_RIGHT))
			X += SPEED;

		//All if's below made to bounce sprite of window borders
		if (yTop) {
			Y += BOUNCE_MOVEMENT_STEP;
			std::this_thread::sleep_for(std::chrono::nanoseconds(SLEEP_TIME));
		}

		if (Y > dimension.top + BOUNCE_DISTANCE) {
			yTop = false;
		}

		if (xRight) {
			X -= BOUNCE_MOVEMENT_STEP;
			std::this_thread::sleep_for(std::chrono::nanoseconds(SLEEP_TIME));
		}

		if (X + pictureWidth < dimension.right - BOUNCE_DISTANCE) {
			xRight = false;
		}

		if (yBot) {
			Y -= BOUNCE_MOVEMENT_STEP;
			std::this_thread::sleep_for(std::chrono::nanoseconds(SLEEP_TIME));
		}

		if (Y + pictureHeight < dimension.bottom - BOUNCE_DISTANCE) {
			yBot = false;
		}

		if (xLeft) {
			X += BOUNCE_MOVEMENT_STEP;
			std::this_thread::sleep_for(std::chrono::nanoseconds(SLEEP_TIME));
		}

		if (X > dimension.left + BOUNCE_DISTANCE) {
			xLeft = false;
		}

		//Collisions check
		if (Y <= dimension.top) {
			yTop = true;
			Y = dimension.top;
			InvalidateRect(winHandle, NULL, FALSE);
		}
		if (X + pictureWidth >= dimension.right) {
			xRight = true;
			X = dimension.right - pictureWidth;
			InvalidateRect(winHandle, NULL, FALSE);
		}
		if (Y + pictureHeight >= dimension.bottom) {
			yBot = true;
			Y = dimension.bottom - pictureHeight;
			InvalidateRect(winHandle, NULL, FALSE);
		}
		if (X <= dimension.left) {
			xLeft = true;
			X = dimension.left;
			InvalidateRect(winHandle, NULL, FALSE);
		}

		//Redraw
		InvalidateRect(winHandle, NULL, FALSE);
	}
	delete sprite;

	return 0;
}