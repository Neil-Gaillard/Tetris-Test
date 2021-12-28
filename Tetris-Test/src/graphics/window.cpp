#include "window.hpp"

namespace graphics {

	void window_resize(GLFWwindow* window, int width, int height);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	Window::Window(const unsigned int width, const unsigned int height, const char* title) : m_Height(height), m_Width(width), m_Title(title)
	{
		if (!init())
			glfwTerminate();
		for (int i = 0; i < MAX_KEYS; i++)
			m_keys[i] = false;
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	bool Window::init()
	{
		if (!glfwInit())
			return false;

		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
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

	void Window::clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::update()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	bool Window::isKeyPressed(unsigned int keycode) const
	{
		if (keycode >= MAX_KEYS)
			return false;
		return m_keys[keycode];
	}

	bool Window::closed() const
	{
		return glfwWindowShouldClose(m_Window) == 1;
	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_keys[key] = action == GLFW_PRESS || action == GLFW_REPEAT;
	}

	void window_resize(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
}