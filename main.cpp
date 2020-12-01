#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <Windows.h>
using namespace std;
using namespace sf;

int windowx = 1024;
int windowy = 1024;
RenderWindow window(VideoMode(windowx, windowy), "SFML Fractal", Style::Close | Style::Titlebar | Style::Resize);

VertexArray lines(LineStrip, 2);
vector <Vector2f> coords;

int main()
{
	lines[1].position = Vector2f(256, 251);
	lines[0].position = Vector2f(256, 261);
	coords.push_back(lines[0].position);
	coords.push_back(lines[1].position);
	window.draw(lines);
	window.display();
	Sleep(1000);
	while (window.isOpen())
	{
		Event evnt;
		while (window.pollEvent(evnt))
		{
			if (evnt.type == Event::Closed)
			{
				window.close();
			}
		}
		//Updating Fractal
		Vector2f pivot = coords[coords.size() - 1];

		vector <Vector2f> copy;
		for (int i = coords.size()-1; i>=0; i--)
		{
			Vector2f point = coords[i];
			point.x -= pivot.x;
			point.y -= pivot.y;
			copy.push_back(Vector2f(point.y + pivot.x, -point.x + pivot.y));
		}
		for (int i = 0; i < copy.size(); i++)
		{
			coords.push_back(copy[i]);
		}

		if (Mouse::isButtonPressed(Mouse::Right))
		{
			//Zoom out
			for (int i = 0; i < coords.size(); i++)
			{
				coords[i].x *= 0.5;
				coords[i].y *= 0.5;
			}
			cout << "You pressed your Right Mouse Button" << endl;
		}

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			//Zoom in
			for (int i = 0; i < coords.size(); i++)
			{
				coords[i].x /= 0.5;
				coords[i].y /= 0.5;
			}
			cout << "You pressed your Left Mouse Button" << endl;
		}
		if (GetAsyncKeyState(VK_LEFT) & 0x0001) //move left
		{
			for (int i = 0; i < coords.size(); i++)
			{
				coords[i].x -= 100;
			}
		}
		if (GetAsyncKeyState(VK_UP) & 0x0001) //move up
		{
			for (int i = 0; i < coords.size(); i++)
			{
				coords[i].y -= 100;
			}
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x0001) //move right
		{
			for (int i = 0; i < coords.size(); i++)
			{
				coords[i].x += 100;
			}
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x0001) //move down
		{
			for (int i = 0; i < coords.size(); i++)
			{
				coords[i].y += 100;
			}
		}
		lines.clear();
		lines.resize(coords.size());
		for (int i = 0; i < coords.size(); i++)
		{
			lines[i] = coords[i];
		}
		//Drawing Fractal
		window.clear();
		window.draw(lines);
		window.display();
		Sleep(1000);
	}
}
