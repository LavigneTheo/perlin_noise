#pragma once
#include "GLFW/glfw3.h"
#include <iostream>

class Window
{
	private:
		GLFWwindow* m_window;
		int WIDTH, HEIGHT;
		static bool m_key_pressed[256];

		static Window* INSTANCE;

		Window() {}
	public:
		void build(const int& width, const int& height);

		GLFWwindow* get_GLFWWindow() const;

		const int getHeight() const;
		const int getWidth() const;
		
		static Window* get_instance();
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		bool* get_key_pressed() const;

		~Window();
};
