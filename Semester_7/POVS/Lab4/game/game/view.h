#include <SFML/Graphics.hpp>
using namespace sf;

// ���������� ������� ������ ���, ��� �������� ������� ����
View view;

View setCoordToView(float x, float y)
{
	// ���������� ������ ����� �� ������
	// ����� ���������� ���������� ���������
	float tmpX = x;
	float tmpY = y;
	// ��������� ������ �� ���������� ����������, ���� ��� ���� �������
	// ��� ����� ������ ��������� solid, ����� ���� ������ �� 
	// ������ ���� �� ����
	
	if (x < 640) tmpX = 640;
	//if (y < 360) tmpY = 360;
	if (y > 500) tmpY = 500;
	if (x > 1536) tmpX = 1536;


	// ����� ���������� ������ � ����������� ������, ����� �� ���
	view.setCenter(tmpX,tmpY);
	// ����������� ������
	return view;
}

// �������� ����� �� ���������
View scrollView(float time)
{
	// ���� ������ ������ �������, ������ ������� ������ �� ����������
	// ������ ������������ ���������� ����� ������� �� ��������
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		view.move(0.2 * time, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		view.move(0, 0.2 * time);
	}
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		view.move(-0.2 * time, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		view.move(0, -0.2 * time);
	}
	// �����������(����������� ������)
	return view;
}
