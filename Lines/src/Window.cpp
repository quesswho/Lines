#include "Window.h"
#include <iostream>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void window_resize(GLFWwindow *window, int width, int height);

Window::Window(int width, int height, const char* title, double multiply)
	: m_width(width), m_height(height), m_title(title), value(multiply)
{
	if (!init())
	{
		std::cout << "Terminating in 5 seconds!\n";
		Sleep(5000);
		Window::~Window();
	}
	std::cout << "Successfully created window!\n";
}

Window::~Window()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

bool Window::init()
{
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW\n";
		return false;
	}
	window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
	if (!window)
	{
		std::cout << "Failed to create Window!\n";
		return false;
	}
	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, this);
	glfwSetWindowSizeCallback(window, window_resize);
	glfwSetKeyCallback(window, key_callback);

	if (!glewInit() == GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW!\n";
		return false;
	}
	return true;
}

void Window::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::Update()
{
	glfwPollEvents();
	glfwSwapBuffers(window);
}

bool Window::Closed()
{
	return glfwWindowShouldClose(window);
}

void window_resize(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
		win->value++;
	if (key == GLFW_KEY_LEFT)
		win->value -= 0.01;
	if (key == GLFW_KEY_RIGHT)
		win->value += 0.01;
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
		win->value--;
}