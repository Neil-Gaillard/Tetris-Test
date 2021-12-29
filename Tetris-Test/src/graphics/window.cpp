#include "window.hpp"

#include <GL/glew.h>

namespace graphics {

	void window_resize(GLFWwindow* window, const int width, const int height);
	static void key_callback(GLFWwindow* window, const int key, int scancode, const int action, int mods);

	Window::Window(const int width, const int height, const char* title) : m_Title(title), m_Height(height), m_Width(width)
	{
		if (!init())
			glfwTerminate();
		for (bool& m_key : m_keys)
			m_key = false;
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	bool Window::init()
	{
		if (!glfwInit())
			return false;

		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, nullptr, nullptr);
		if (!m_Window) {
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, this);
		glfwSetWindowSizeCallback(m_Window, window_resize);
		glfwSetKeyCallback(m_Window, key_callback);

		if (glewInit() != GLEW_OK)
			return false;
		return true;
	}

	void Window::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::update() const
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	bool Window::isKeyPressed(const int keycode) const
	{
		if (keycode >= MAX_KEYS)
			return false;
		return m_keys[keycode];
	}

	bool Window::closed() const
	{
		return glfwWindowShouldClose(m_Window) == 1;
	}

	void key_callback(GLFWwindow* window, const int key, int scancode, const int action, int mods)
	{
		const auto win = static_cast<Window*>(glfwGetWindowUserPointer(window));
		win->m_keys[key] = action == GLFW_PRESS || action == GLFW_REPEAT;
	}

	void window_resize(GLFWwindow* window, const int width, const int height)
	{
		glViewport(0, 0, width, height);
	}
}