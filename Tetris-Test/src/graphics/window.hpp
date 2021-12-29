#pragma once

// ReSharper disable once CppUnusedIncludeDirective
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace graphics {

#define MAX_KEYS 1024

	class Window
	{
	private:
		const char* m_Title;
		GLFWwindow* m_Window{};
		int m_Height;
		int m_Width;

		bool m_keys[MAX_KEYS]{};

	public:
		Window(const int width, const int height, const char* title);
		~Window();

		static void clear();
		void update() const;

		bool closed() const;

		inline int getWidth() const { return this->m_Width; }
		inline int getHeight() const { return this->m_Height; }

		bool isKeyPressed(int keycode) const;

	private:
		bool init();
		friend void window_resize(GLFWwindow* window, int width, int height);
		friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	};
}