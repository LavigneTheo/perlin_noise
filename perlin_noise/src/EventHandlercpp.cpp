#include "EventHandler.h"

EventHandler::EventHandler(const Window* window) : m_window(window){

}

void EventHandler::process_event() {
	bool* key_pressed = m_window->get_key_pressed();

	if (key_pressed[GLFW_KEY_W]) {
		octave++;
		key_pressed[GLFW_KEY_W] = false;
		std::cout << octave << std::endl;
	}
		
	if (key_pressed[GLFW_KEY_S]) {
		octave--;
		key_pressed[GLFW_KEY_S] = false;
		std::cout << octave << std::endl;
	}

	if (key_pressed[GLFW_KEY_R]) {
		m_perlin2D.change_bias(0.2f);
		key_pressed[GLFW_KEY_R] = false;
		std::cout << m_perlin2D.get_bias() << std::endl;
	}
	
	if (key_pressed[GLFW_KEY_T]) {
		m_perlin2D.change_bias(-0.2f);
		key_pressed[GLFW_KEY_T] = false;
		std::cout << m_perlin2D.get_bias() << std::endl;
	}
	
	if (key_pressed[GLFW_KEY_A]) {
		key_pressed[GLFW_KEY_A] = false;
		if (m_mode == perlin1D)
			m_perlin1D_V2.create_noise(2000);
		else if (m_mode == perlin2D)
			m_perlin2D_V2.create_noise_fractal_sum(5);
	}
		
	
}

void EventHandler::draw() {

	if (m_mode == perlin1D) {
		glBegin(GL_POINTS);
		m_perlin1D_V2.draw();
	}
	else if (m_mode == perlin2D) {
		glBegin(GL_QUADS);
		m_perlin2D_V2.draw();
	}
	
	glEnd();
}