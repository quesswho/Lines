#include <iostream>
#include "Window.h"
#include <math.h>

// 38.04 39, 51, 72, 124, 249, 501

struct Vec2 {
	float m_x, m_y;
	Vec2(float x, float y)
		: m_x(x), m_y(y)
	{}
	Vec2()
		: m_x(0), m_y(0)
	{}
};

void drawLine(float x1, float y1, float x2, float y2);

#define LINES 701
#define RADIUS 0.9
#define PI 3.14159265

	Window *window;
	Vec2 locations[LINES];
	 
int main() {
	double multiply = 1;
	window = new Window(1280, 720, "Lines", multiply);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	

	float addDegree = 360.0 / LINES;
	float degree = 0.0f;
	//Calculate all positions in a circle
	for (int i = 0; i < LINES; i++) {
		locations[i] = Vec2(RADIUS*cos(degree * PI / 180.0), RADIUS*sin(degree * PI / 180.0));
		//std::cout << RADIUS * cos(degree * PI / 180.0) << ", " << RADIUS*sin(degree * PI / 180.0) << std::endl;
		degree += addDegree;
	}

	glViewport(0, 0, window->m_width, window->m_height);
	glMatrixMode(GL_PROJECTION);
	float aspect = (float)window->m_width / (float)window->m_height;
	glOrtho(-aspect, aspect, -1, 1, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	while (!window->Closed())
	{
		window->Clear();
		for (int i = 0; i < LINES-1; i++) //circle
		{
			//drawLine(0, 0, locations[i].m_x, locations[i].m_y);
			//drawLine(locations[i].m_x, locations[i].m_y, locations[i+1].m_x, locations[i+1].m_y);
		}

		for (int i = 0; i < LINES; i++)
		{
			if (i*multiply <= LINES && multiply>=0)
				drawLine(locations[i].m_x, locations[i].m_y, locations[int(i*multiply)].m_x, locations[int(i * multiply)].m_y);
			else if (multiply <= 0) // Negative numbers
			{
				double j = i * multiply;
				while (j <= LINES)
					j += LINES;
				drawLine(locations[i].m_x, locations[i].m_y, locations[int(j - 1)].m_x, locations[int(j - 1)].m_y);
			} else {
				double j = i * multiply;
				while (j >= LINES)
					j -= LINES;
				drawLine(locations[i].m_x, locations[i].m_y, locations[int(j-1)].m_x, locations[int(j-1)].m_y);
			}
		}

		glColor3f(1, 0, 0);
		window->Update();
		multiply = window->value;
		std::cout << multiply << std::endl;
	}
	return 0;
}

void drawLine(float x1, float y1, float x2, float y2)
{
	glBegin(GL_LINES);
	glVertex3f(x1, y1, 0);
	glVertex3f(x2, y2, 0);
	glEnd();
}