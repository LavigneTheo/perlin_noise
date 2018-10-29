#pragma once
#include <algorithm>
#include "GLFW/glfw3.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

class Perlin1D_V2 {
private:
	static const unsigned int m_max_vertices = 64;
	int m_size;
	float m_random[m_max_vertices];
	float* m_perlin = nullptr;
	
	float eval(const float& x);
	float eval_periodic(const float& x);
	float eval_periodic_cosine(const float& x);
	float eval_periodic_smoothstep(const float& x);
	float eval_signed_periodic_smoothstep(const float& x);

	float lerp(const float& xLow, const float& xHigh, const float& t);

	
public:
	Perlin1D_V2();
	~Perlin1D_V2() {
		if (m_perlin != nullptr)
			free(m_perlin);
	}

	void create_noise(const int& num_steps);
	void make_rand();
	void draw();
};