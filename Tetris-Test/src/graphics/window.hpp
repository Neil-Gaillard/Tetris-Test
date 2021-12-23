#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace graphics {

#define MAX_KEYS 1024

	class Window
	{
	private:
		const char* m_Title;
		GLFWwindow* m_Window;
		unsigned int m_Height;
		unsigned int m_Width;
		bool m_Closed;

		bool m_keys[MAX_KEYS];

	public:
		Window(const unsigned int width, const unsigned int height, const char* title);
		~Window();

		void clear() const;
		void update();

		bool closed() const;

		inline unsigned int getWidth() const { return this->m_Width; }
		inline unsigned int getHeight() const { return this->m_Height; }

		bool isKeyPressed(unsigned int keycode) const;

	private:
		bool init();
		friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	};
}