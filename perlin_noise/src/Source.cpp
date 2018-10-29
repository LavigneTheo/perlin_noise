#include <algorithm>
#include <string>
#include <iostream>
#include "GLFW/glfw3.h"
#include <time.h>
#include "Window.h"
#include "EventHandler.h"

using namespace std;


int main() {
	int test = 5 % 10;
	Window* window = Window::get_instance();
	window->build(1000, 500);

	EventHandler event_handler(window);

	//glfwSwapInterval(10);

	while (!glfwWindowShouldClose(window->get_GLFWWindow()))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		event_handler.process_event();
		event_handler.draw();

		/* Swap front and back buffers */
		glfwSwapBuffers(window->get_GLFWWindow());

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;

	return 0;
}
