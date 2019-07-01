#pragma once

#include <Windows.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
private:
	const char* m_title;
	GLFWwindow* window;
public:
	int m_height, m_width;
	double value;
	Window(int height, int width, const char* title, double multiply);
	~Window();

	void Clear();
	void Update();

	bool Closed();
private:
	bool init();
};