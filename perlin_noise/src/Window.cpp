#include "Window.h"

Window* Window::INSTANCE = nullptr;
bool Window::m_key_pressed[256];

Window::~Window() {
	delete INSTANCE;
}

Window* Window::get_instance() {
	if (INSTANCE == nullptr)
		INSTANCE = new Window;
	return INSTANCE;
}

void Window::build(const int& width, const int& height) {

	WIDTH = width; HEIGHT = height;

	/* Initialize the library */
	if (!glfwInit())
		std::cout << "Error while initializing GLFW" << std::endl;

	/* Create a windowed mode window and its OpenGL context */
	m_window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", NULL, NULL);

	if (!m_window)
	{
		glfwTerminate();
		std::cout << "Error while creating the window" << std::endl;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(m_window);
	//if (glewInit() != GLEW_OK)
		//std::cout << "Error while initializing GLEW" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;

	glfwSetKeyCallback(m_window, this->key_callback);
}


void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	/******************************** PRESSED *******************************/

	if (action == GLFW_PRESS && key == GLFW_KEY_W)
		m_key_pressed[GLFW_KEY_W] = true;
	if (action == GLFW_PRESS && key ==  GLFW_KEY_S)
		m_key_pressed[GLFW_KEY_S] = true;
	if (action == GLFW_PRESS && key == GLFW_KEY_D)
		m_key_pressed[GLFW_KEY_D] = true;
	if (action == GLFW_PRESS && key == GLFW_KEY_A)
		m_key_pressed[GLFW_KEY_A] = true;
	if (action == GLFW_PRESS && key == GLFW_KEY_R)
		m_key_pressed[GLFW_KEY_R] = true;
	if (action == GLFW_PRESS && key == GLFW_KEY_T)
		m_key_pressed[GLFW_KEY_T] = true;

	/******************************** RELEASE *******************************/

	if (action == GLFW_RELEASE && key == GLFW_KEY_W)
		m_key_pressed[GLFW_KEY_W] = false;
	if (action == GLFW_RELEASE && key == GLFW_KEY_S)
		m_key_pressed[GLFW_KEY_S] = false;
	if (action == GLFW_RELEASE && key == GLFW_KEY_D)
		m_key_pressed[GLFW_KEY_D] = false;
	if (action == GLFW_RELEASE && key == GLFW_KEY_A)
		m_key_pressed[GLFW_KEY_A] = false;
	if (action == GLFW_RELEASE && key == GLFW_KEY_R)
		m_key_pressed[GLFW_KEY_R] = false;
	if (action == GLFW_RELEASE && key == GLFW_KEY_T)
		m_key_pressed[GLFW_KEY_T] = false;

}

bool* Window::get_key_pressed() const {
	return m_key_pressed;
}

GLFWwindow* Window::get_GLFWWindow() const {
	return m_window;
}

const int Window::getHeight() const {
	return HEIGHT;
}
const int Window::getWidth() const {
	return WIDTH;
}