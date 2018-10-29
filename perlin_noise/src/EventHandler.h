#pragma once
#include "Window.h"
#include <GLFW/glfw3.h>
#include "perlin/Perlin1D.h"
#include "perlin/Perlin1D_V2.h"
#include "perlin/Perlin2D.h"
#include "perlin/Perlin2D_V2.h"

typedef enum Mode {
	perlin1D = 0, perlin2D = 1
};

class EventHandler {
private:
	const Window* m_window;
	Perlin1D m_perlin1D;
	Perlin1D_V2 m_perlin1D_V2;

	Perlin2D m_perlin2D;
	Perlin2D_V2 m_perlin2D_V2;
	unsigned int octave = 4;
	Mode m_mode = perlin2D;
public:

	EventHandler(const Window* window);

	void process_event();
	void draw();
};
